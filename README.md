NonLinear Engine
=============

<!--=====================================================================================-->
<p>
<b>3D Game and Simulation Engine</b>
</p>

<hr width="100%">

<h3>About the Project</h3>
<p>
NonLinear Engine is a completely free open-source 3D game and simulation engine for Windows.
The goal of this project is to create a very fast, scalable, and highly customizable platform that provides a solid foundation to independent game developers and hobbyists for their games. 
</p>

<p>
I started this project as a means to practice what I am passionate about which is game and graphics development. I enjoy experimenting with modern game technologies and rendering techniques, and I think that you will find it being reflected in my design.
</p>

<p>
I hope that some of you will find this project useful. All feedback is highly appreciated. 
</p>
<hr width="100%">


<!--=====================================================================================-->
<p>
<h5>Current Features:</h5>
<ul>
  <li>
    loading of scenes from a variety of common interchange formats. See the link  below for a full list of                        formats:<br/>
    http://assimp.sourceforge.net/main_features_formats.html
  </li>
  <li>
    support for DDS, BMP, JPEG, PNG, TIFF, GIF, HD Photo texture formats
  </li>
  <li>
    support for texture block compression
  </li>
  <li>
    static scene rendering using Direct3D 11
  </li>
  <li>
    first-person camera for scene exploration
  </li>
  <li>
    UI displaying FPS and user controls
  </li>
  <li>
    windowed and fullscreen modes
  </li>
  <li>
    loading of precompiled shaders from file
  </li>
  <li>
    support for shading technique swaps at runtime
  </li>
  <li>
    abstraction of all OS and graphics API specific functionality
  </li>
  <li>
    DLL and Application build configurations
  </li>
  <li>
    easy integration into existing applications
  </li>
  <li>
    modular component design
  </li>
</ul>
</p>

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
<h3>Roadmap</h3>
This section is created to track development progress and includes completed and pending tasks as well as future plans.

<table style="width:100%">
  <tr>
    <td><b>Step #</b></td>
    <td><b>Description</b></td>
    <td><b>Status</b></td>
  </tr>
  
  <tr>
    <td>...</td>
    <td>Release the first stable version V1.0.0</td>
    <td>Future Plans</td>
  </tr>
  <tr>
    <td>...</td>
    <td>Upgrade to Direct3D 12 to impove rendering performance and scalability</td>
    <td>Future Plans</td>
  </tr>
  <tr>
    <td>...</td>
    <td>...</td>
    <td>...</td>
  </tr>
  <tr>
    <td>...</td>
    <td>Integrate Mono Scripting system for high flexibility and customization</td>
    <td>Future Plans</td>
  </tr>
  <tr>
    <td>26</td>
    <td>Redesign the architecture to improve scalability</td>
    <td><b>Pending</b></td>
  </tr>
  <tr>
    <td>25</td>
    <td><b>Begin working on V1.0.0</b></td>
    <td><b>Pending</b></td>
  </tr>
  <tr>
    <td>24</td>
    <td>Finalize the prototyping stage</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>23</td>
    <td>Implement engine systems interfaces and expose them through the DLL boundary</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>22</td>
    <td>Add DLL build configurations for integration into existing applications</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>21</td>
    <td>Implement FPS counter</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>20</td>
    <td>Connect engine systems with input processor</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>19</td>
    <td>Write event conversion maps for GLFW and CEGUI to engine event system</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>18</td>
    <td>Implement an event system with a simple input processor</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>17</td>
    <td>Implement an application layer using GLFW library</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>16</td>
    <td>Add support for GUI rendering</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>15</td>
    <td>Integrate scriptable GUI using CEGUI</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>14</td>
    <td>Implement a first-person camera</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>13</td>
    <td>Implement a basic scene manager</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>12</td>
    <td>Implement a texture loader using DirectXTex library</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>11</td>
    <td>Implement a model importer using Assimp library</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>10</td>
    <td>Add support for shader compilation and loading of precompiled shaders</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>9</td>
    <td>Write vertex and pixel shaders for simple forward rendering</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>8</td>
    <td>Implement basic rendering engine supporting rendering of static geometry with diffuse materials</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>7</td>
    <td>Encapsulate shading techniques into objects and make them swappable at runtime</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>6</td>
    <td>
      Implement rendering device encapsulating Direct3D 11 state management.
    </td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>5</td>
    <td>Write DirectXMath abstraction layer</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>4</td>
    <td>Write Direct3D 11 abstraction layer</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>3</td>
    <td>Choose graphics API</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>2</td>
    <td>Add logging support</td>
    <td>Complete</td>
  </tr>
  <tr>
    <td>1</td>
    <td>Design modular engine architecture</td>
    <td>Complete</td>
  </tr>
</table>
<hr width="100%">

<!--=====================================================================================-->
<h3>Current & Pending Releases</h3>
<hr width="20%">
<p>
  None at this time
</p>
<hr width="100%">

<!--=====================================================================================-->
<h5>Downloads:</h5>
<p>
  None at this time<br/>
  Examples will become available as the development progresses
</p>
<hr width="100%">

<!--=====================================================================================-->
<h5>Build Instructions:</h5>
<ol>
  <li>
    Download and install Visual Studio 2013 (VS2013 Express is sufficient)
    http://www.visualstudio.com/downloads/download-visual-studio-vs
  </li>
  <li>
    Download and unzip dependencies, and throw their contents into the NonLinear Engine root directory.
  </li>
  <li>
    Navigate to the NLE directory and open the project file in Visual Studio.
  </li>
  <li>
    Select the desired platform and configuration, then select Build -> Build Solution from the main menu.
  </li>
</ol>
<hr width="100%">

<!--=====================================================================================-->
<h3>Licensing</h3>
NonLinear engine is licensed under the MIT license.
