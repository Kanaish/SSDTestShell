# SSDTestShell
> SSD implemented as SW and Test shell for SSD

## Contributors
We are **Code, Love You** team! 🙂 <br/><br/>
<a href="https://github.com/Kanaish/SSDTestShell/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=Kanaish/SSDTestShell" />
</a>

## Getting started
### Clone Repository
```shell
{YourDirectory} > git clone https://github.com/Kanaish/SSDTestShell.git
{YourDirectory} > cd SSDTestShell
```

### Build
Open `SSDTestShell.sln` with Visual Studio. 
(We used Visual Studio 2022 in Windows 10-11.)
Build > Solution Build with Debug mode in Visual Studio.

### Execute
You can find `SSDManager.exe` and `TestShell.exe` in `./x64/Debug/`.
`SSDManager.exe` get arguments and `TestShell.exe` do not.
```shell
{YourDirectory}/SSDTestShell/ > cd x64/Debug
{YourDirectory}/SSDTestShell/x64/Debug/ > SSDManager.exe {Arguments}
{YourDirectory}/SSDTestShell/x64/Debug/ > TestShell.exe
```
You can execute many test scenarios with runner.
We provides example scenario list file - `/resources/run_list.lst`
```shell
{YourDirectory}/SSDTestShell/x64/Debug/ > TestShell.exe {ScenarioListFileName}
```

## Features
 * SSD validate input, read(R), write(W), erase(E), flush(F).
	* SSD stores data in `/resources/nand.txt`.
	* SSD has its own command buffer - `/resources/buffer.txt` - to decrease direct access count to SSD.
	* Fast read from buffer if there is stored W/E requests in command buffer.
	* Command buffer stores commands with optimization.
	* The result of read request from SSD is stored in `/resources/result.txt`
 * TestShell provides many commands.
	* validate input, write, read, fullwrite, fullread, exit, and help
	* erase, erase_range, flush.
	* testapp1, testapp2 and runner.
 * SSD API library is used in TestShell to send request to SSD.
 * Logs are printed in command line and save with files in `/log/`.
	* Log format is `[<Date> <Time>] <Class Name>::<Function Name>() : <Log Message>`. 50bytes are fixed before `:`.
	* You can log with `LOG()` after include `"LogManager.h"`.
	* `/log/latest.log` is latest. The max size of 1 log file is 10KB. 
	* When exceeds 10KB, the file renames to `/log/until_{date}_{time}.log`.
	* When 2 log files are created, the oldest is zipped. (Actually rename from `.log` to `.zip`.)

## Usage
Here's all of the configurations you can enter when execute .exe files.

### SSDManager.exe
Be careful - SSDManager is case insensitive.

`SSDManager.exe w <LBA> <data>`
  - Writes `<data>` to `<LBA>`.
  - `<data>` have to be hexa numeric.
  - Example: `w 3 0xAAAABBBB`
  - Sends command to ssd.

`SSDManager.exe r <LBA>`
  - Reads from `<LBA>`.
  - Example: `read 3`
  - Sends command to ssd.
  - Outputs the result to the screen from `/resources/result.txt`.

 `SSDManager.exe e <LBA> <SIZE>`
  - Erases data from `<LBA>` for `<SIZE>` LBAs.
 `<SIZE>` can be ranged in 0 to 10.
  - Example: `erase 3 10`
  - Erases data from LBA 3 through LBA 12.

`SSDManager.exe f`
  - Flushes the command buffer.
  - Example: `flush`
  - Sends all buffered commands to ssd.

### TestShell.exe
Enter below commands after execute `Testshell.exe`.
Be careful - TestShell is case sensitive.

`write <LBA> <data>`
  - Writes `<data>` to `<LBA>`.
 `<data>` have to be hexa numeric.
  - Example: `write 3 0xAAAABBBB`
  - Sends command to ssd.

`read <LBA>`
  - Reads from `<LBA>`.
  - Example: `read 3`
  - Sends command to ssd.
  - Outputs the result to the screen from `/resources/result.txt`.

`fullwrite <data>`
  - Writes `<data>` to all LBAs (0~99).
 `<data>` have to be hexa numeric.
  - Example: `fullwrite 0xABCDFFFF`
  - Writes 0xABCDFFFF to all LBAs.

`fullread`
  - Reads from all LBAs (0~99).
  - Example: `fullread`
  - Outputs all LBA values to the screen.
 Value stored in LBA99 is written in `/resources/result.txt`.

 `erase <LBA> <SIZE>`
  - Erases data from `<LBA>` for `<SIZE>` LBAs.
 `<SIZE>` can be ranged in 0 to 100.
  - Example: `erase 3 10`
  - Erases data from LBA 3 through LBA 12.

 `erase_range <Start LBA> <End LBA>`
  - Erases data from `<Start LBA>` through `<End LBA>` - 1.
  - Example: `erase_range 3 13`
  - Erases data from LBA 3 through LBA 12.

`flush`
  - Flushes the command buffer.
  - Example: `flush`
  - Sends all buffered commands to ssd.

`exit`
  - Exits the shell.

`help`
  - Displays usage instructions for all commands.

`testapp1`
  - Executes test scenario 1.
  - `fullwrite 0xAAAABBBB` then `fullread`.

`testapp2`
  - Executes test scenario 2. Aging test.
  - Writes 0xAAAABBBB to LBA0~5 30 times.
  - Then writes 0x12345678 to LBA0~5.
  - Then reads LBA0~5.
