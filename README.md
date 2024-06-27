<h1>C-Web-Server</h1>

<h2>Build from Source</h2>

<p>
    <h6>using <strong>cl</strong> from <strong>MSVC</strong> on <strong>Windows</strong>:</h6><br>
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
    using <strong>gcc</strong> on <strong>Unix-like systems</strong> e.g. <strong>Linux</strong>:<br>
    sys/socket.h and netinet/in.h are included in the libc library, which is linked by default, so you don’t need to explicitly link any additional libraries when compiling on Unix-like systems.<br>
    run: <code>gcc main.c</code><br>
</p>

<h2>Install Compiler</h2>

<p>
    Install <strong>cl</strong> from <strong>MSVC</strong> on <strong>Windows</strong>:<br>
    You can install the <strong>Desktop development with C++</strong> workload without a full Visual Studio IDE installation. From the Visual Studio <a href="https://visualstudio.microsoft.com/downloads/">Downloads</a> page, scroll down until you see <strong>Tools for Visual Studio</strong> under the <strong>All Downloads</strong> section and select the download for <strong>Build Tools for Visual Studio</strong>.<br>
</p>

<p>
    Install <strong>gcc</strong> from <strong>MinGW</strong> on <strong>Windows</strong>:<br>
    soon<br>
</p>

<p>
    Install <strong>gcc</strong> on <strong>Unix-like systems</strong> e.g. <strong>Linux</strong>:<br>
    For Debian based Linux distributions, gcc can be installed via the <code>apt</code> package manager.<br>
    run: <code>apt install gcc</code><br>
</p>
