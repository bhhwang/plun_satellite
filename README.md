plun_satellite
==============

remote controller(satellite) for plun project.
Open source platform을 기반으로 plun software와 연동되어 사물인터넷 시스템을 구성할 수 있도록 지원하기 위함이고, platform의 spec에 따라 지원하는 내용은 차이가 있을 수 있습니다.

지원 계획은 아래와 같으며 필요에따라 호환 하드웨어로 대체될 수 있습니다.
개발에 필요한 주요 문서는 각 프로젝트의 reference 디렉토리에 있습니다.


* TI Launchpad
    
    (1) 지원 모델

    * MSP430F5529 Launchpad + CC3000 WiFi module
    * TM4C123GH6PM Launchpad + CC3000 WiFi module
   
    (2) 설치
    
    * [Stellaris ICDI Driver](http://www.ti.com/tool/stellaris_icdi_drivers)
    * [Code Composer Studio for the Tiva C Series TM4C123G LaunchPad](http://www.ti.com/tool/sw-ek-tm4c123gxl)
    * [TivaWare for C Series Software (Complete) 151M ](http://software-dl.ti.com/tiva-c/SW-TM4C/latest/index_FDS.html)
    * [CC3000 SDK](http://www.ti.com/litv/zip/swrc282)
  
  
* Arduino


* ARM mbed

Getting Started
===============
1. Download CCS, TivaWare and Drivers which depends on your device.
2. on the CCS Menu, Help > Eclipse Marketplace > Find 'Egit' > Install
3. on the 'Project Explorer' of CCS, click right button then select import > import > Git > Project from Git
4. Enter the this repository URL(https://github.com/bhhwang/plun_satellite) on window for git clone.
5. You can freely use this source code under the MIT License.


License
===============
You can freely use, modify, redistribute this source code under the MIT License.