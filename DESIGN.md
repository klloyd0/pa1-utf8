Question 1

On one end, UTF-32 could prevent the possibility of codepoints consisting of 4 bytes from failing to load, such as emojis or special characters. On the other hand, not only would it take up more storage, but characters needing only 1 byte such as ASCII would ultimately just waste the other 3 front bytes on entirely 0's.

Question 2