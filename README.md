Mô tả:
- Chương trình đọc dữ liệu từ file, mỗi lần lấy tối đa 80.000.000 bytes ~ 5.000.000 khỗi mã AES 128bit
- Chương trình lấy key từ file hexa, sinh IV ngẫu nhiên
- encode_CBC.cpp: Mã nguồn mã hóa AES với CBC mode
- decode_CBC.cpp: Mã nguồn giải mã CBC mode
- encode_CTR: Mã nguồn mã hóa hóa Counter mode(CTR)
- decode_CTR: Mã nguồn giải mã CTR mode
- encode.h: Mã nguồn chứa các hàm dùng để mã hóa AES
- decode.h: Mã nguồn chứa các hàm dùng để giải mã AES
- keyfile: Chứa key

Cài đặt: https://github.com/wind123mountain/AES-CBC-CTR-mode
- g++ encode_CBC.cpp -o encode_CBC
- g++ decode_CBC.cpp -o decode_CBC
- g++ encode_CBC.cpp -o encode_CBC
- g++ decode_CBC.cpp -o decode_CBC

Sử dụng: <trình mã hóa/giải mã> <tên file đầu vào>
- CBC mode:

![image](https://user-images.githubusercontent.com/57493825/114276967-42e1f600-9a53-11eb-9fe2-984063c58492.png)

- CTR mode:

![image](https://user-images.githubusercontent.com/57493825/114277047-af5cf500-9a53-11eb-85a7-155045326703.png)

CBC mode sử dụng thư viện pycrypto:
 
![image](https://user-images.githubusercontent.com/57493825/114277912-7030a300-9a57-11eb-871c-7bf1339921bd.png)
 
![image](https://user-images.githubusercontent.com/57493825/114277905-6870fe80-9a57-11eb-9baa-cf2863fdaf31.png)
 
![image](https://user-images.githubusercontent.com/57493825/114277825-116b2980-9a57-11eb-9c03-c7a35f10349c.png)
  
![image](https://user-images.githubusercontent.com/57493825/114276967-42e1f600-9a53-11eb-9fe2-984063c58492.png)


Tham khảo code AES:
- Chương trình sử dụng code cài đặt AES từ: https://github.com/ceceww/aes
để tạo ra các file 'encode.h' và 'decode.h'
