$fileList=Get-ChildItem -Recurse -Include *.template
foreach($f in $fileList)
{
  $dst = $f.FullName.Substring(0, $f.FullName.Length  - ".template".length)
  Copy-Item -Path $f[0] -Destination $dst
}