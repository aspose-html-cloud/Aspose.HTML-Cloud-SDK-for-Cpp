@echo off
rem Thin wrapper around sign.ps1. Credentials come from environment variables or
rem the gitignored signing.local.env (template: signing.local.env.example).
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0sign.ps1" %*
exit /b %ERRORLEVEL%
