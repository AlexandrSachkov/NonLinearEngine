NonLinear Engine
=============

<!--=====================================================================================-->
<p>
<b>Data-Parallel 3D Game Engine for Windows</b>
</p>

<hr width="100%">

<h3>About the Project</h3>
<p>
NonLinear Engine is a completely free (MIT Licensed) experimental 3D game engine for Windows. The aim of this project is to develop a highly scalable game engine that fully utilizes processors with a large number of cores (6 cores +) through the use of its custom parallel framework, and then push it to see what is possible to achieve. Possible use cases include: achieving higher frame rates, more dynamic bodies and animations, smarter AI, higher graphical detail, approximated voxel terrain, real-time fluid simulations,  etc.
</p>

<p>
Borrowing ideas from Intel's <a href="https://software.intel.com/en-us/articles/designing-the-framework-of-a-parallel-game-engine">Designing the Framework of a Parallel Game Engine</a>, NonLinear Engine framework features free-step system execution with variable execution frequencies and lockless parallel data synchronization between systems. It is built on top of <a href="https://www.threadingbuildingblocks.org/">Intel TBB</a> task scheduler and heavily utilizes its parallel containers and algorithms for efficient parallelization and minimization of memory contention. The framework is decoupled from the engine and can be built separately for uses in other projects.
</p>

<p>
This engine if far from completion and is currently in an active state of development. Throughout the development, I will be posting working samples and tutorials and updating documentation for stable components. I started this project as a means to practice what I am passionate about which is game and graphics development. It has been an amazing learning experience working on this engine as I learned about engine architectures, rendering APIs and techniques, memory management, and parallelization techniques, and improved my C++ skills to a level far beyond what I could have through sheer university curriculum. 
</p>
<hr width="100%">

<!--=====================================================================================-->
<h3>Contact</h3>
<p>
If you are interested in this project and would like to contribute, feel free to contact me at: <br/>
ale<b>k</b>sach<b>x</b>ov@hotmail.com <br/>
(Anti-bot, flip the bold characters)
</p>
<hr width="100%">

<!--=====================================================================================-->
<p>
<h3>Current Features:</h3>
<ul>
  <li>
    Written in modern C++ 14
  </li>
  <li>
    CMake build system
  </li>
  <li>
    Modular architecture
  </li>
  <li>
    Decoupled from the presentation layer (Embeddable)
  </li>
  <li>
    Cross-platform (except for the rendering system)
  </li>
  <li>
    Input system
  </li>
  <li>
    Direct3D 11 Rendering system
  </li>
  <li>
    First-person camera
  </li>
  <li>
    <a href="http://assimp.sourceforge.net/index.html">Assimp</a> scene importer supporting a large number of interchange        formats </br>
    .dae, .blend, .3ds, .obj, .x, and <a href="http://assimp.sourceforge.net/main_features_formats.html">more…</a>
  </li>
  <li>
    <a href="https://directxtex.codeplex.com/">DirectXTex</a> texture importer supporting mipmap generation and the following     texture formats: </br>
	  DDS, BMP, JPEG, PNG, TIFF, GIF, HD Photo
  </li>
  <li>
    Loading precompiled shaders from file and compiling on the fly
  </li>
  <li>
    FPS counter
  </li>
  <li>
    Windowed and fullscreen modes
  </li>
</ul>
</p>
<hr width="100%">

<!--=====================================================================================-->
<h3>Roadmap</h3>
This section is created to track development progress and includes completed and pending tasks as well as future plans.

<table style="width:100%">
  <tr>
    <td><b>Step #</b></td>
    <td><b>Description</b></td>
    <td><b>Status</b></td>
  </tr>
  
  <tr>
    <td>11</td>
    <td>Add shadows</td>
    <td>Pending</td>
  </tr>
  <tr>
    <td>10</td>
    <td>Add material support</td>
    <td>Pending</td>
  </tr>
  <tr>
    <td>9</td>
    <td>Add support for blending</td>
    <td>Pending</td>
  </tr>
  <tr>
    <td>8</td>
    <td>Add support for forward lighting</td>
    <td>Pending</td>
  </tr>
  <tr>
    <td>7</td>
    <td>Build Simple Direct3D 11 rendering system</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>6</td>
    <td>Build basic input system</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>5</td>
    <td>Build basic application system</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>4</td>
    <td>Build parallel engine core</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>3</td>
    <td>Write a basic functional build system in CMake</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>2</td>
    <td>Select a cross-platform build system (CMake)</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>1</td>
    <td>Finalize the prototyping stage V.0.1.0</td>
    <td>Complete</td>
  </tr>
</table>
<hr width="100%">

<!--=====================================================================================-->

<h3>Versioning</h3>
<p>
All NonLinear Engine versions follow the format stated below:<br/>
<b>[Major Version].[Minor Version].[Patch Version]</b><br/>
</p>

<table style="width:100%">
  <tr>
  <td><b>Version</b></td>
  <td><b>Description</b></td>
  </tr>
  <tr>
    <td><b>Major</b></td>
    <td>
      signifies incompatible changes to public API and incorporates changes from Minor and Patch versions. <b>0</b> denotes a       pre-release version while <b>>=1</b> denotes a stable release.
    </td> 
  </tr>
  <tr>
    <td><b>Minor</b></td>
    <td>
     signifies backwards compatible public API changes. Incorporates changes from Patch versions.
    </td> 
  </tr>
    <tr>
    <td><b>Patch</b></td>
    <td>
      signifies bug fixes and changes that do not affect public API. Significance may vary.
    </td> 
  </tr>
</table>
<hr width="100%">

<!--=====================================================================================-->
<h3>Releases:</h3>
<p>
  V0.1.0 prototype is out and contains legacy code.
</p>
<hr width="100%">

<!--=====================================================================================-->
<h3>Downloads:</h3>
<p>
  No binary releases at this time<br/>
  Examples will become available as the development progresses
</p>
<hr width="100%">

<!--=====================================================================================-->
<h3>Build Instructions:</h3>
Detailed instructions will be posted when the engine core is ready.
<hr width="100%">

<!--=====================================================================================-->
<h3>Licensing</h3>
NonLinear engine is licensed under the MIT license.
