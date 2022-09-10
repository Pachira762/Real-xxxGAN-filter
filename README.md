# Real-xxxGAN-filter
Real-CUGAN��Real-ESRGAN��Aviutl��Ŏg����悤�ɂ���v���O�C���ł��B  
���ɕs����ȃv���O�C���ł��B
PC��I�v�V�����ɂ���Ă͋N�����Ȃ���������o�͂���Ȃ�������n���O�A�b�v�����肵�܂��B
�����̃v���W�F�N�g�Ɏg���ꍇ�̓o�b�N�A�b�v���Ƃ邱�Ƃ��������߂��܂��B
  
## �C���X�g�[��
`Plugins`�t�H���_��`Real-xxxGAN-filter.auf`��`Models`�t�H���_���R�s�[���܂��B
  
## �g����
**�X�P�[��**  
�g�嗦�ł�. x4plus��x4plus-anime��4�{�ɂȂ�܂��B  
**�f�m�C�Y**  
�m�C�Y�����@�\�ł�. �������傫���قǋ��������܂��B  
Real-CUGAN�ł̂ݗL���ɂȂ�܂��B  
**TTA**  
�A�[�e�B�t�@�N�g���팸�ł��܂��B  
���ɏd���ł��B  
  
## �r���h
**Vulkan SDK**  
[�����T�C�g](https://www.lunarg.com/vulkan-sdk/)����C���X�g�[���[�_�E�����[�h��*SDK 32-bit Core Components*�Ƀ`�F�b�N�����C���X�g�[�����܂��B  
���ϐ�`Vulkan_INCLUDE_DIR`�ɃC���X�g�[�����`Include`�t�H���_�A`Vulkan_LIBRARY`�ɃC���X�g�[�����`Lib`�t�H���_��ݒ肵�܂��B  

**ncnn**  
[how to build](https://github.com/Tencent/ncnn/wiki/how-to-build#build-for-windows-x64-using-visual-studio-community-2017)�ɂ���������`x64`��`Win32`�ɒu�������ăr���h���܂��B  
�v���W�F�N�g�̒ǉ��̃C���N���[�h�f�B���N�g����`build\install\include\ncnn`���A�ǉ��̃��C�u�����f�B���N�g����`build\install\lib`��ǉ����܂��B
Vulkan SDK�Ƃ̍�����h������`build\install\lib`�ɐ������ꂽ`SPIRV.lib`��`SPIRV-ncnn.lib`�Ƀ��l�[�����܂��B  
    
**realcugan-ncnn-vulkan**  
```shell
git clone https://github.com/nihui/realcugan-ncnn-vulkan.git
cd Real-ESRGAN-ncnn-vulkan
mkdir build 
cd build
cmake -A Win32 ..
cmake --build . --generate-spirv
```
`realcugan.h` `realcugan.cpp`�A`build`�t�H���_�������ꂽ`*.hex.h`�t�@�C�����v���W�F�N�g�t�H���_�ɃR�s�[���܂��B
  
**realcugan-esrgan-vulkan**  
��Ɠ����悤�Ƀr���h��`realesrgan.h` `realesrgan.cpp`�A`*.hex.h*`�t�@�C�����v���W�F�N�g�t�H���_�ɃR�s�[���܂�  
  
## License
### [Real-CUGAN](https://github.com/bilibili/ailab/tree/main/Real-CUGAN)
MIT License

Copyright (c) 2022 bilibili

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

---

### [realcugan-ncnn-vulkan](https://github.com/nihui/realcugan-ncnn-vulkan)
The MIT License (MIT)

Copyright (c) 2019 nihui

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

---

### [Real-ESRGAN](https://github.com/xinntao/Real-ESRGAN)
BSD 3-Clause License

Copyright (c) 2021, Xintao Wang
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

---

### [Real-ESRGAN-ncnn-vulkan](https://github.com/nihui/realcugan-ncnn-vulkan)
The MIT License (MIT)

Copyright (c) 2021 Xintao Wang

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

---

### AviUtlPluginSDK
The MIT License

Copyright (c) 1999-2012 Kenkun

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

---

### Real-xxxGAN-filter
MIT License

Copyright (c) 2022 Pachira762

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
