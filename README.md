## FOO_PLAYBACK_TO_FILE
This project is an opensource-copy of foo_simple_np plugin which is not supported by latest foobar2000 player

### Compiled versions dowload


[foo_playback_to_file_x32](https://sourceforge.net/projects/foo-playback-to-file/files/x32/foo_playback_to_file.dll/download)
[foo_playback_to_file_x64](https://sourceforge.net/projects/foo-playback-to-file/files/x64/foo_playback_to_file.dll/download)

### Usage
1. Get latest [foobar2000 SDK](https://www.foobar2000.org/SDK) and extract it into `lib\foobar2000_sdk` directory \
2. Retarget project for your Visual Studio version and adjust project include settings if necessary
3. Open `foo_playback_to_file.sln`, select `OK` when asked whether to update compiler/libraries for old projects
4. Build!
5. `foo_playback_to_file.dll` will be generated at `Debug`, `Release` or `x64` directory depending on your configuration
6. To load the component in foobar2000, copy the `foo_playback_to_file.dll` into `foobar2000\components` directory
