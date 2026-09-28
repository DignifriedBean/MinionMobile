$ErrorActionPreference = "Stop"

$ProjectRoot = Split-Path -Parent (Split-Path -Parent $MyInvocation.MyCommand.Path)
$ProjectFile = Join-Path $ProjectRoot "MinionMobile.uproject"
$EngineConfig = Join-Path $ProjectRoot "Config\DefaultEngine.ini"
$SourceFile = Join-Path $ProjectRoot "Source\MinionMobile\MinionMobileGameMode.cpp"

function Assert-FileContains {
	param(
		[string]$Path,
		[string]$Pattern,
		[string]$Message
	)

	$Text = Get-Content -LiteralPath $Path -Raw
	if ($Text -notmatch $Pattern) {
		throw $Message
	}
}

if (!(Test-Path -LiteralPath $ProjectFile)) {
	throw "Missing MinionMobile.uproject."
}

if (!(Test-Path -LiteralPath $EngineConfig)) {
	throw "Missing Config\DefaultEngine.ini."
}

$ProjectJson = Get-Content -LiteralPath $ProjectFile -Raw | ConvertFrom-Json
if ($ProjectJson.EngineAssociation -ne "5.8") {
	throw "Project EngineAssociation must be 5.8."
}

if ($ProjectJson.TargetPlatforms -notcontains "Android") {
	throw "Project TargetPlatforms must include Android."
}

Assert-FileContains $EngineConfig "PackageName=com\.codex\.minionmobile" "Android PackageName is not configured."
Assert-FileContains $EngineConfig "MinSDKVersion=26" "MinSDKVersion should be 26."
Assert-FileContains $EngineConfig "TargetSDKVersion=35" "TargetSDKVersion should be 35."
Assert-FileContains $EngineConfig "bBuildForArm64=True" "ARM64 packaging is not enabled."
Assert-FileContains $EngineConfig "bBuildForArmV7=False" "ARMv7 should be disabled."
Assert-FileContains $EngineConfig "bPackageDataInsideApk=True" "APK data packaging is not enabled."
Assert-FileContains $EngineConfig "r\.MobileHDR=False" "Mobile HDR should be disabled."
Assert-FileContains $EngineConfig "r\.DefaultFeature\.Bloom=False" "Bloom should be disabled."
Assert-FileContains $SourceFile "constexpr int32 Rows = 10;" "Minion row count is not 10."
Assert-FileContains $SourceFile "constexpr int32 Columns = 10;" "Minion column count is not 10."
Assert-FileContains $SourceFile "Expected exactly 100 primitive minions" "Exact 100-minion assertion is missing."

$ImportedAssetExtensions = @("*.fbx", "*.obj", "*.glb", "*.gltf", "*.png", "*.jpg", "*.jpeg", "*.tga", "*.wav", "*.mp3")
$ImportedAssets = foreach ($Extension in $ImportedAssetExtensions) {
	Get-ChildItem -Path $ProjectRoot -Recurse -File -Filter $Extension -ErrorAction SilentlyContinue |
		Where-Object { $_.FullName -notmatch "\\(\.git|work|outputs)\\" }
}

if ($ImportedAssets) {
	$List = ($ImportedAssets | Select-Object -ExpandProperty FullName) -join [Environment]::NewLine
	throw "Imported assets are present, which violates the built-in-only requirement:$([Environment]::NewLine)$List"
}

Write-Host "Android project configuration validated."
Write-Host "Built-in-only asset audit passed."
Write-Host "Runtime scene generation is configured for exactly 100 minions."
