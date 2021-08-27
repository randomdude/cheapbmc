
 param (
    [Parameter(Mandatory=$true)][string]$filename,
    [Parameter(Mandatory=$true)][string]$settingname,
    [Parameter(Mandatory=$true)][string]$newval
 )

$x = [xml](get-content $filename)
$x.SelectSingleNode("configuration//userSettings//*//setting[@name='$settingname']").Value = $newval
$x.save($filename)