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
The goal of this project is to create a very fast, stable, and highly customizable platform that provides a solid foundation to independent game developers and hobbyists for their games. 
</p>

<p>
I started this project as a means to practice what I am passionate about which is game and graphics development. I enjoy experimenting with modern game technologies and rendering techniques, and I think that you will find it being reflected in my design.
</p>

<p>
I hope that some of you will find this project useful. All feedback is highly appreciated. 
</p>
<hr width="100%">

<!--=====================================================================================-->

<h3>Versioning</h3>
<p>
All NonLinear Engine versions follow the format stated below:<br/>
<b>[Major Version].[Minor Version].[Interface Version]</b><br/>
</p>

<table style="width:100%">
  <tr>
  <td><b>Version</b></td>
  <td><b>Description</b></td>
  </tr>
  <tr>
    <td><b>Major</b></td>
    <td>
      signifies major architectural changes. Always worth upgrading to. <b>0</b> denotes prototype while <b>>=1</b> denotes          stable release.
    </td> 
  </tr>
  <tr>
    <td><b>Minor</b></td>
    <td>
     signifies changes that do not affect overall architecture. Significance may vary.
    </td> 
  </tr>
    <tr>
    <td><b>Interface</b></td>
    <td>
      signifies changes to engine interfaces. May affect integration with existing applications.
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
    <td>Release the first stable version V1.0.1</td>
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
    <td>30</td>
    <td>Design and implement a highly scalable engine architecture using Intel TBB</td>
    <td>Future Plans</td>
  </tr>
  <tr>
    <td>29</td>
    <td><b>Release V0.1.1 Prototype with an example</b></td>
    <td><b>Pending</b></td>
  </tr>
   <tr>
    <td>28</td>
    <td>Fix rendering bug associated with UI rendering</td>
    <td><b>Pending</b></td>
  </tr>
  <tr>
    <td>27</td>
    <td>Modify shaders to support normal, reflection and transparency maps</td>
    <td><b>Pending</b></td>
  </tr>
  <tr>
    <td>26</td>
    <td>Add light importing functionality</td>
    <td><b>Pending</b></td>
  </tr>
  <tr>
    <td>25</td>
    <td>Smooth out camera movement</td>
    <td><b>Pending</b></td>
  </tr>
  <tr>
    <td>24</td>
    <td>Add camera controls window to the UI</td>
    <td><b>Pending</b></td>
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

<!--=====================================================================================-->
<p>
<h4>V0.1.1 Prototype</h4>
<b>Status: 95% Complete</b>
</p>

<!--=====================================================================================-->
<p>
<h5>Purpose:</h5> 
<ul>
  <li>
    to identify architectural requirements
  </li>
  <li>
    to better understand and solve challenges associated with with game and rendering engine development
  </li>
  <li>
    to learn and evaluate the chosen external libraries and middleware
  </li>
  <li>
    to show something for all my hard work
  </li>
</ul>
</p>

<!--=====================================================================================-->
<p>
<h5>Features:</h5>
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
    support for swapping of shading techniques at runtime
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
  <li>
    well-managed complexity
  </li>
</ul>
</p>

<!--=====================================================================================-->
<h5>Warning:</h5>
This is a <b>prototype</b> release and should be treated as such. It is not an accurate representation of the actual product. Use at your own risk. 

<!--=====================================================================================-->
<h5>Download Binaries:</h5>
Will become available upon release

<!--=====================================================================================-->
<h5>Dependencies:</h5>
<ul>
  <li>
    Boost C++ 1.55.0 filesystem<br/>
    http://www.boost.org/
  </li>
  <li>
    Assimp 3.1.1<br/>
    http://assimp.sourceforge.net/index.html
  </li>
  <li>
    CEGUI 0.8.4<br/>
    http://cegui.org.uk/
  </li>
  <li>
    GLFW 3.0.4<br/>
    http://www.glfw.org/
  </li>
</ul>

<!--=====================================================================================-->
<h5>Build Instructions:</h5>
<ol>
  <li>
    Download and install Visual Studio 2013 if you dont have it installed already<br/>
    http://www.visualstudio.com/downloads/download-visual-studio-vs
  </li>
  <li>
    Build Dependencies:<br/>  
  <p>
    Follow links in the "Dependencies" section for library-specific build instructions. Every library must be built as a          shared library (Multi-Threaded DLL), otherwise NonLinear Engine will not build under DLL configurations. The only required     part of Boost is Filesystem, and you can use bjam commands stated below to build it:<br/>
  </p>
  <p>
    bjam --with-filesystem --toolset=msvc --stagedir=stage32debug address-model=32 variant=debug link=static threading=multi      runtime-link=shared<br/><br/>
    bjam --with-filesystem --toolset=msvc --stagedir=stage32release address-model=32 variant=release link=static                  threading=multi runtime-link=shared<br/><br/>
    bjam --with-filesystem --toolset=msvc --stagedir=stage64debug address-model=64 variant=debug link=static threading=multi      runtime-link=shared<br/><br/>
    bjam --with-filesystem --toolset=msvc --stagedir=stage64release address-model=64 variant=release link=static                  threading=multi runtime-link=shared<br/><br/>
  </p>
  </li>
</ol>

<b>I will write the rest tomorrow</b>

<hr width="100%">
<!--=====================================================================================-->
<h3>Licensing</h3>
NonLinear engine is licensed under the MIT license.
