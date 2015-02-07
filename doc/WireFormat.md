# Data format

The data shall be stored in one or more files on the SD card. A new
file shall be created
 - when the device is powered on (start of new session);
 - when the current session timer exceeds `0xffffff` (around 1193 hours
   or just under fifty days).

A file shall consist of a file header followed by zero or more
dataframes.

A file header shall be `16` bytes as follows:

 - 1:     Magic number, `0xec`.
 - 2:     Magic number, `0x09`.
 - 3:     Format version, `0x00`.
 - 4-6:   Unused.
 - 7-14:  Unsigned big-endian integer representing the number of
          milliseconds since 1970-01-01T00:00:00:00Z at the start of the
          session.
 - 15-16: Unsigned big-endian integer `S`, the number of channels
          (equivalently, samples per frame).

A dataframe shall be `N = 8 + 4S` bytes as follows:

 - 1:     Packet counter which cycles from `0x00` to `0xff`.
 - 2-5:   Unsigned 32-bit big-endian integer representing the time in
          milliseconds since the start of the session.
 - 5-8:   Unused.
 - 9-N:   `S` sample frames.

A sample frame shall be a 4-byte big-endian unsigned integer.
