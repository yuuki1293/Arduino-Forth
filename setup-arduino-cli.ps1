Invoke-WebRequest -Uri "https://downloads.arduino.cc/arduino-cli/arduino-cli_latest_Windows_64bit.zip" -OutFile "bin/arduino-cli.zip"
Expand-Archive -Path bin\arduino-cli.zip -DestinationPath bin\