<#
Versions: Windows 10 Home

Dependencies: none
#>

$user = [Security.Principal.WindowsIdentity]::GetCurrent();
$admin = (New-Object Security.Principal.WindowsPrincipal $user).IsInRole([Security.Principal.WindowsBuiltinRole]::Administrator);

if ($admin -eq $false)
{
    Write-Output "User is not Admin."
    $return
}
