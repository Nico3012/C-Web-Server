# C-Web-Server

<h2>Build from Source</h2>

using cl from MSVC on Windows:
link ws2_32.lib (static libs on windows are named *.lib)
<code>cl main.c /link ws2_32.lib</code>

using gcc from MinGW on Windows:
link libws2_32.a (static libs on linux are named lib*.a)
MinGW ports the GNU Compiler Collection from Linux to Windows. Therefore, static libs are named lib*.a
<code>gcc main.c -l:libws2_32.a</code>
