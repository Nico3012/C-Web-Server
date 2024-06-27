<h1>C-Web-Server</h1>

<h2>Build from Source</h2>

<p>
    using <strong>cl</strong> from <strong>MSVC</strong> on <strong>Windows</strong>:<br>
    link ws2_32.lib (static libs on windows are named *.lib)<br>
    run: <code>cl main.c /link ws2_32.lib</code><br>
</p>

<p>
    using <strong>gcc</strong> from <strong>MinGW</strong> on <strong>Windows</strong>:<br>
    link libws2_32.a (static libs on linux are named lib*.a)<br>
    MinGW ports the GNU Compiler Collection from Linux to Windows. Therefore, static libs are named lib*.a<br>
    The <code>-l ws2_32</code> flag adds lib*.a itself and would therefore do the same as <code>-l:libws2_32.a</code>.<br>
    run: <code>gcc main.c -l:libws2_32.a</code><br>
</p>

<p>
    using <strong>gcc</strong> on <strong>Unix-like systems</strong>:<br>
    sys/socket.h and netinet/in.h are included in the libc library, which is linked by default, so you don’t need to explicitly link any additional libraries when compiling on Unix-like systems.
    run: <code>gcc main.c</code><br>
</p>
