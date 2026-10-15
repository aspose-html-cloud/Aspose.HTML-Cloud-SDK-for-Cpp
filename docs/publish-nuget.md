# Publishing the Aspose.Html-Cloud.Cpp NuGet package

> Secrets (SSL.com eSigner credentials, NuGet API key) are **never** committed.
> Put them in `signing.local.env` (gitignored; template: `signing.local.env.example`)
> or set them as environment variables.

## Prerequisites

- `nuget.exe` on `PATH` (or a full path to it).
- SSL.com CodeSignTool unpacked into `CodeSignTool\` (gitignored; it bundles its own JDK).
  Download: https://www.ssl.com/guide/esigner-codesigntool-command-guide/
- `signing.local.env` with `SSLCOM_USERNAME`, `SSLCOM_PASSWORD`, `SSLCOM_CREDENTIAL_ID`,
  `SSLCOM_TOTP_SECRET`, `NUGET_API_KEY` (same eSigner account as the .NET SDK).

## 1. Build / pack

Build the `x64` and `Win32` `Debug`/`Release` configurations first (see `aspose.html.cloud.nuspec` `<files>`), then:

```powershell
nuget.exe pack .\aspose.html.cloud.nuspec -OutputDirectory . -BasePath .
```

## 2. Sign

```powershell
.\sign.ps1                 # version is read from aspose.html.cloud.nuspec
# or: .\sign.ps1 -Version 26.8.1
```

The script temporarily switches the CodeSignTool timestamper to `http://timestamp.digicert.com`
(NuGet.org rejects the default ssl.com timestamp with NU3023) and restores
`CodeSignTool\conf\code_sign_tool.properties` afterwards.

> Sign only for the final publication: each signing operation is billed.

## 3. Verify

```powershell
nuget.exe verify -Signatures .\signed\Aspose.Html-Cloud.Cpp.<version>.nupkg
```

Must print `Successfully verified package`.

## 4. Push

The API key must be scoped to `Aspose.Html-Cloud.Cpp` (https://www.nuget.org/account/apikeys).

```powershell
nuget.exe push .\signed\Aspose.Html-Cloud.Cpp.<version>.nupkg -Source https://api.nuget.org/v3/index.json -ApiKey $env:NUGET_API_KEY
```

## Troubleshooting

- **403 Forbidden on push**: the API key has no permission for this package; create a key scoped to `Aspose.Html-Cloud.Cpp`.
- **NU3023: timestamp certificate key too short**: the package was signed with the ssl.com timestamper; re-sign with `sign.ps1`.
- **Package does not appear on NuGet.org**: signature validation is asynchronous and bad timestamps are rejected silently; always verify locally first.

## Notes

- Code-signing certificate expires **2028-11-05**.
- NuGet.org organisation: https://www.nuget.org/organization/asposecloud
