<h1>C-Web-Server</h1>

<h2>Build from Source</h2>

<p>using cl from MSVC on Windows:</p>
<p>link ws2_32.lib (static libs on windows are named *.lib)</p>
<code>cl main.c /link ws2_32.lib</code>

<p>using gcc from MinGW on Windows:</p>
<p>link libws2_32.a (static libs on linux are named lib*.a)</p>
<p>MinGW ports the GNU Compiler Collection from Linux to Windows. Therefore, static libs are named lib*.a</p>
<code>gcc main.c -l:libws2_32.a</code>
