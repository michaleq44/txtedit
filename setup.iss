#define MyAppName "txtedit"
#define MyAppVersion "1.2.2"
#define MyAppPublisher "michaleq44"
#define MyAppURL "https://github.com/michaleq44/txtedit"
#define MyAppExeName "bin\txtedit.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{68FD985F-1A35-4156-802A-7FD2B68F5310}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\{#MyAppName}
UninstallDisplayIcon={app}\{#MyAppExeName}
; "ArchitecturesAllowed=x64compatible" specifies that Setup cannot run
; on anything but x64 and Windows 11 on Arm.
ArchitecturesAllowed=x64compatible
; "ArchitecturesInstallIn64BitMode=x64compatible" requests that the
; install be done in "64-bit mode" on x64 or Windows 11 on Arm,
; meaning it should use the native 64-bit Program Files directory and
; the 64-bit view of the registry.
ArchitecturesInstallIn64BitMode=x64compatible
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
LicenseFile=D:\Michalo\C\txtedit\LICENSE
InfoBeforeFile=D:\Michalo\C\txtedit\preinstall.rtf
InfoAfterFile=D:\Michalo\C\txtedit\postinstall.rtf
; Remove the following line to run in administrative install mode (install for all users).
PrivilegesRequired=lowest
PrivilegesRequiredOverridesAllowed=dialog
OutputDir=D:\Michalo\C\txtedit\release
OutputBaseFilename=txtedit v{#MyAppVersion}-win64-setup
SetupIconFile=D:\Michalo\C\txtedit\data\icon.ico
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "D:\Michalo\C\txtedit\build\release\{#MyAppExeName}"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "D:\Michalo\C\txtedit\LICENSE"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Michalo\C\txtedit\data\icon.ico"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Michalo\C\txtedit\README.md"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Michalo\C\txtedit\data\icon.png"; DestDir: "{app}\data"; Flags: ignoreversion
Source: "D:\Michalo\C\txtedit\data\style.css"; DestDir: "{app}\data"; Flags: ignoreversion
Source: "D:\Michalo\C\txtedit\release\share\*"; DestDir: "{app}\share"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\Michalo\C\txtedit\release\bin\*"; DestDir: "{app}\bin"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent
Filename: "appwiz.cpl"; Description: "Open Programs and Features so you can remove your old text editor"; Flags: nowait postinstall shellexec skipifsilent

