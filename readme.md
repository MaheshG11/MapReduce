<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]

<!-- PROJECT LOGO -->
<br />
<div align="center">


<h1 align="center">MapReduce</h1>
<h2 align="center">An implementation of MapReduce with dynamic node allocation</h2>
  <p align="center">
    <br />
    <br />
    <br />
 <!--   <a href="https://github.com/MaheshG11/MapReduce">View Demo</a> -->
    
<!--     <a href="https://github.com/MaheshG11/MapReduce/issues/new?labels=bug&template=bug-report---.md">Report Bug</a> -->
    
<!--     <a href="https://github.com/MaheshG11/MapReduce/issues/new?labels=enhancement&template=feature-request---.md">Request Feature</a> -->
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
     <a href="#getting-started">Getting Started</a>
     <!--  <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>-->
    </li>
 <!--    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>-->
    <li><a href="#contributing">Contributing</a></li>
<!--     <li><a href="#license">License</a></li> -->
    <li><a href="#contact">Contact</a></li>
<!--     <li><a href="#acknowledgments">Acknowledgments</a></li> -->
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

<!--[![Product Name Screen Shot][product-screenshot]](https://example.com)-->

<!-- MapReduce with Dynamic node allocation -->
<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With
* [![C++][C++]][C++-url]
* [![Docker][Docker]][Docker-url]
* [gRPC][gRPC-url]


<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

Follow the below installations to setup.
<!--
### Prerequisites

This is an example of how to list things you need to use the software and how to install them.
* npm
  ```sh
  npm install npm@latest -g
  ```-->

### Installation

1. Fork the Project
2. In a seperate empty clone forked the repo
    ```bash
    git clone git@github.com:<YOUR-USERNAME>/MapReduce.git
    ```
3. Set the official repository as your upstream to synchronize with the latest update in the this repository. Add the original repository as upstream 
    ```bash
    cd MapReduce
    git remote add upstream git@github.com:MaheshG11/MapReduce.git
    ```
4. Synchronize latest commit with this repository before coding 
    ```bash
    git fetch upstream
    ```
5. Installation </br>a. For Windows: If you use windows you will have to work with docker or WSL.
      ```bash
      docker build -t map_reduce .
      docker run -it map_reduce
      ```
      b. For Linux : Make sure cmake is not installed initially as we will use newer version of cmake installed through grpc
      ```bash
      sudo ./gRPCinstall.sh # installing grpc
      sudo ./initialize.sh # compiling code
      ```
      #### NOTE: Compiled executable will be found in project_dir/out/build/
6. Possible Errors </br>
      a. For Linux: if during compilation you recieve <b>cmake not found</b>, try 
      ```bash
      export PATH="$HOME/.local/bin:$PATH"
      ``` 
      and then run the compilation command.
7. Linking You working directory to project container
    ```bash
    docker run -it -v ./:/project map_reduce 
    # Assuming that you are docker from source directory 
    # i.e, where dockerfile is located
    ```

</br>

    
  
<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
<!--
## Usage

Use this space to show useful examples of how a project can be used. Additional screenshots, code examples and demos work well in this space. You may also link to more resources.

_For more examples, please refer to the [Documentation](https://example.com)_

<p align="right">(<a href="#readme-top">back to top</a>)</p>

-->



<!-- CONTRIBUTING -->



<!-- LICENSE -->
<!-- CONTACT -->
## Contact

Mahesh Ghumare [LinkedIn](https://www.linkedin.com/in/mahesh-ghumare-37894a200/)


<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/MaheshG11/MapReduce.svg?style=for-the-badge
[contributors-url]: https://github.com/MaheshG11/MapReduce/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/MaheshG11/MapReduce.svg?style=for-the-badge
[forks-url]: https://github.com/MaheshG11/MapReduce/network/members
[stars-shield]: https://img.shields.io/github/stars/MaheshG11/MapReduce.svg?style=for-the-badge
[stars-url]: https://github.com/MaheshG11/MapReduce/stargazers
[issues-shield]: https://img.shields.io/github/issues/MaheshG11/MapReduce.svg?style=for-the-badge
[issues-url]: https://github.com/MaheshG11/MapReduce/issues
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/mahesh-ghumare-37894a200
[product-screenshot]: images/screenshot.png

[Docker]:https://img.shields.io/badge/docker-%230db7ed.svg?style=for-the-badge&logo=docker&logoColor=white
[Docker-url]:https://www.docker.com/
[C++]:https://img.shields.io/badge/-C++-blue?logo=cplusplus
[C++-url]:https://isocpp.org/
[gRPC-url]: https://grpc.io/
[gRPC]: https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcRtgakfOXSN05s2chm6ZJOm7msQXYo4HYWEUA&s
