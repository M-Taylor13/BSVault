[Setup]
AppName=BSVault
AppVersion=1.0.0
DefaultDirName={commonpf}\BSVault
DefaultGroupName=BSVault
OutputDir=C:\Users\madis\OneDrive\Coding\BSVault\BSVault\build\Desktop_Qt_6_10_0_MinGW_64_bit-Release1\installer
OutputBaseFilename=BSVaultInstaller
SetupIconFile=C:\Users\madis\OneDrive\Coding\BSVault\BSVault\build\Desktop_Qt_6_10_0_MinGW_64_bit-Release1\BSVault.ico
Compression=lzma
SolidCompression=yes
ArchitecturesInstallIn64BitMode=x64compatible

[Files]
Source: "C:\Users\madis\OneDrive\Coding\BSVault\BSVault\build\Desktop_Qt_6_10_0_MinGW_64_bit-Release1\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
; Desktop shortcut
Name: "{commondesktop}\BSVault"; Filename: "{app}\BSVault.exe"; IconFilename: "{app}\BSVault.ico"

; Start Menu shortcut
Name: "{group}\BSVault"; Filename: "{app}\BSVault.exe"; IconFilename: "{app}\BSVault.ico"

; Uninstall shortcut
Name: "{group}\Uninstall BSVault"; Filename: "{uninstallexe}"

[Run]
Filename: "{app}\BSVault.exe"; Description: "Launch BSVault"; Flags: nowait postinstall skipifsilent

[Code]

function ConfirmUninstall(): Boolean;
begin
  Result := MsgBox(
    'WARNING: All your BSVault data will be deleted permanently!' + #13#10 +
    'This action cannot be undone.' + #13#10 + #13#10 +
    'Do you want to continue?',
    mbConfirmation, MB_OKCANCEL
  ) = IDOK;
end;

procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
var
  VaultPath: String;
begin
  if CurUninstallStep = usUninstall then
  begin
    VaultPath := ExpandConstant('{userappdata}\BSVault');

    if DirExists(VaultPath) then
      DelTree(VaultPath, True, True, True);
  end;
end;