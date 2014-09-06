NonLinear Engine
=============

<!--=====================================================================================-->
<p>
<b>3D Game and Simulation Engine</b>
</p>

<hr width="50%">

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
<hr width="50%">

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
<hr width="50%">

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
    <td>29</td>
    <td>Design and implement a highly scalable engine architecture using Intel TBB</td>
    <td>Future Plans</td>
  </tr>
  <tr>
    <td>28</td>
    <td><b>Release V0.1.1 Prototype with an example</b></td>
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
