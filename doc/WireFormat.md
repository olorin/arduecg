# Data format

The data shall be stored in one or more files on the SD card. A new
file shall be created
 - when the device is powered on (start of new session);
 - when the current session timer exceeds `0xffffff` (around 1193 hours
   or just under fifty days).

A file shall consist of a file header followed by zero or more
dataframes.

A file header shall be eleven bytes as follows:

 - 1:     Magic number, `0xec`.
 - 2:     Magic number, `0x09`.
 - 3:     Format version, `0x00`.
 - 4-11:  Unsigned big-endian integer representing the number of
          milliseconds since 1970-01-01T00:00:00:00Z at the start of the
          session.

A dataframe shall be seventeen bytes as follows:

 - 1:     Packet counter which cycles from `0x00` to `0xff`.
 - 2-5:   Unsigned 32-bit big-endian integer representing the time in
          milliseconds since the start of the session.
 - 6-7:   Channel 0 sample.
 - 8-9:   Channel 1 sample.
 - 10-11: Channel 2 sample.
 - 12-13: Channel 3 sample.
 - 14-15: Channel 4 sample.
 - 16-17: Channel 5 sample.

A sample shall be a two-byte big-endian unsigned integer between `0x0000`
and `0x03ff`.
