<h1>C-Web-Server</h1>

<h2>Build from Source</h2>

<p>
    using <strong>cl</strong> from <strong>MSVC</strong> on <strong>Windows</strong>:<br>
    link ws2_32.lib (static libs on windows are named *.lib)<br>
    <code>cl main.c /link ws2_32.lib</code><br>
</p>

<p>
    using <strong>gcc</strong> from <strong>MinGW</strong> on <strong>Windows</strong>:<br>
    link libws2_32.a (static libs on linux are named lib*.a)<br>
    MinGW ports the GNU Compiler Collection from Linux to Windows. Therefore, static libs are named lib*.a<br>
    <code>gcc main.c -l:libws2_32.a</code><br>
</p>
