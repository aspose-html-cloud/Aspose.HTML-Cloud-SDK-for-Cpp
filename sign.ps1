<#
.SYNOPSIS
    Signs the Aspose.Html-Cloud.Cpp NuGet package with SSL.com CodeSignTool.

.DESCRIPTION
    Credentials are NEVER stored in this script. They are taken from environment
    variables, or from the gitignored file `signing.local.env` next to this script
    (see `signing.local.env.example`):

        SSLCOM_USERNAME, SSLCOM_PASSWORD, SSLCOM_CREDENTIAL_ID, SSLCOM_TOTP_SECRET

    CodeSignTool (with its bundled JDK) is expected in .\CodeSignTool (gitignored,
    download from https://www.ssl.com/guide/esigner-codesigntool-command-guide/).

    NuGet.org rejects the default ssl.com timestamp (NU3023), so the script
    temporarily switches the CodeSignTool timestamper to DigiCert and restores the
    original properties file afterwards.

.EXAMPLE
    .\sign.ps1                       # version taken from aspose.html.cloud.nuspec
    .\sign.ps1 -Version 26.8.1
#>
param(
    [string]$Version,
    [string]$EnvFile,
    [string]$OutputDir,
    [string]$TimestampUrl = 'http://timestamp.digicert.com'
)

$ErrorActionPreference = 'Stop'
$root = $PSScriptRoot
if (-not $EnvFile)   { $EnvFile   = Join-Path $root 'signing.local.env' }
if (-not $OutputDir) { $OutputDir = Join-Path $root 'signed' }

# --- credentials -----------------------------------------------------------
if (Test-Path $EnvFile) {
    foreach ($line in Get-Content $EnvFile) {
        if ($line -match '^\s*([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(.*)$') {
            $name = $Matches[1]; $value = $Matches[2].Trim()
            if (-not [Environment]::GetEnvironmentVariable($name, 'Process')) {
                [Environment]::SetEnvironmentVariable($name, $value, 'Process')
            }
        }
    }
}
$required = 'SSLCOM_USERNAME', 'SSLCOM_PASSWORD', 'SSLCOM_CREDENTIAL_ID', 'SSLCOM_TOTP_SECRET'
$missing = $required | Where-Object { -not [Environment]::GetEnvironmentVariable($_, 'Process') }
if ($missing) {
    throw "Missing signing credentials: $($missing -join ', '). Set them as environment variables or in $EnvFile (template: signing.local.env.example)."
}

# --- inputs ----------------------------------------------------------------
if (-not $Version) {
    [xml]$nuspec = Get-Content (Join-Path $root 'aspose.html.cloud.nuspec')
    $Version = $nuspec.package.metadata.version
}
$package = Join-Path $root "Aspose.Html-Cloud.Cpp.$Version.nupkg"
if (-not (Test-Path $package)) { throw "Package not found: $package (run nuget pack first)." }

$toolDir = Join-Path $root 'CodeSignTool'
$java = Get-ChildItem (Join-Path $toolDir 'jdk-*\bin\java.exe') -ErrorAction SilentlyContinue | Select-Object -First 1
$jar  = Get-ChildItem (Join-Path $toolDir 'jar\code_sign_tool-*.jar') -ErrorAction SilentlyContinue | Select-Object -First 1
if (-not $java -or -not $jar) { throw "CodeSignTool not found in $toolDir (expected jdk-*\bin\java.exe and jar\code_sign_tool-*.jar)." }

New-Item -ItemType Directory -Force -Path $OutputDir | Out-Null

# --- temporarily switch timestamper (NuGet.org requires a strong TSA key) ---
$props = Join-Path $toolDir 'conf\code_sign_tool.properties'
$originalProps = [IO.File]::ReadAllText($props)
$exit = 1
try {
    $patched = [regex]::Replace($originalProps, '(?m)^(TIMESTAMPING_URL|TSA_URL|TSA_LEGACY_URL)=.*$', "`$1=$TimestampUrl")
    [IO.File]::WriteAllText($props, $patched)

    $javaArgs = @(
        '-jar', $jar.FullName, 'sign',
        "-username=$env:SSLCOM_USERNAME",
        "-password=$env:SSLCOM_PASSWORD",
        "-credential_id=$env:SSLCOM_CREDENTIAL_ID",
        "-totp_secret=$env:SSLCOM_TOTP_SECRET",
        "-input_file_path=$package",
        "-output_dir_path=$OutputDir",
        '-override=true'
    )
    Push-Location $toolDir
    try {
        & $java.FullName @javaArgs
        $exit = $LASTEXITCODE
    } finally {
        Pop-Location
    }
} finally {
    [IO.File]::WriteAllText($props, $originalProps)
}

if ($exit -ne 0) { throw "CodeSignTool failed with exit code $exit." }
$signed = Join-Path $OutputDir (Split-Path $package -Leaf)
Write-Host "Signed: $signed"
Write-Host "Verify with: nuget.exe verify -Signatures `"$signed`""
