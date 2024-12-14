$files = Get-Item *.jpg

foreach($f in $files){
    Start-Process -FilePath TextureConverter.exe -ArgumentList $f -Wait
}

$files = Get-Item *.png

foreach($f in $files){
    Start-Process -FilePath TextureConverter.exe -ArgumentList $f -Wait
}

$files = Get-Item *.bmp

foreach($f in $files){
    Start-Process -FilePath TextureConverter.exe -ArgumentList $f -Wait
}
pause