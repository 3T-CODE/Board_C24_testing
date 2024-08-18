# Board_C24_testing
## Giới thiệu 
   - Đây là thống kê tình hình test (kiểm thử) board C24 và bao gồm demo một số chức năng hoạt động được đồng thời nêu lên một số chức năng (khối) bị lỗi , xem thêm ở phần Issues 
  Code kiểm thử trong 2 thư mục 'Board_C24_Test' và 'Board_C24_neovim'  , nhưng thư mục 'Board_C24_Test' chưa được hoàn thiện.
  
   - 'Board_C24_neovim' chứa các thư viện , code dành cho việc test các ngoại vi Led , Uart , Ds1307 , MPU6050 , Button
   - 'Board_C24_Test' chứa thư viện , code dành cho việc test TFT ILI9225.
  
## Thống kê tình hình 

  - Các khối chức năng trên board C24 hoạt động bình thường trừ khối I2C2 onboard (Ds1307 và MPU6050 không giao tiếp được) , ngoài ra còn có lỗi ở ký hiệu trên board cụ thể ở phần HC05 ký hiệu bị in ngược .
  
## Demo 

### Led , I2C1
 - Tất cả các led đều hoạt động ổn định , sở dĩ led RGB không sáng được màu xanh dương là do lỗi hàn board hàn sai chiều của led RGB.
  
https://github.com/user-attachments/assets/4d96ffdd-37b0-4d72-a341-007f4002333b

### Button , UART
  - 2 Nút nhấn Button1 và Button2 trên board hoạt động bình thường , các nút khác đều hoạt động ổn định dù không có trong demo, tín hiệu truyền qua UART1 (STM32 -> USB) hoạt động bình thường

https://github.com/user-attachments/assets/fa2e59fe-b2f5-44a6-98a3-c773e669cc39


### UART , I2C 
  - I2C2 onboard (Ds1307 và MPU6050) hoạt động không bình thường , Ds1307 như trong demo không trả về tín hiệu chính xác , tương tự với MPU6050 
  - I2C1 được kết nối với module Ds1307 bên ngoài hoạt động bình thường (xem phần cuối của video demo led)
  - Ngoài ra trong lúc test thì MPU khi kết nối bằng header với I2C2 trên board hoạt động bình thường

https://github.com/user-attachments/assets/e21475a4-c1d6-4625-b237-10e0a6651410


### TFT , SD
  - Đã test qua và hoạt động bình thường bao gồm cả TFT và thẻ SD 


https://github.com/user-attachments/assets/f30f32e9-75a5-45e3-92c9-6646749988c7


https://github.com/user-attachments/assets/3b9b8720-baa0-49c1-a17a-0d1e90820bdf



### Buzzer
  - Tạm chưa có video demo nhưng đã test qua và hoạt động bình thường

### HC05
  - HC05 hoạt động bình thường nhưng ký hiệu trên board bị sai 
  

https://github.com/user-attachments/assets/946d8c8c-7efa-4105-867f-b7c1c30bc5ef


  ![7bee6f7779b8dde684a9](https://github.com/user-attachments/assets/641131f6-7fa7-41f3-86e0-e5adf9844518)

### Esp32 
  - Esp32 trên board hoạt động bình thường , đã thử nạp code và blink led video demo ở trên phần led 

## Notes : 
   - Chi tiết tình hình được liệt kê trong file .docx
   - Code của TFT chưa hoàn thiện do đã làm mất file test ban đầu nên cần làm lại file mới và cần thêm chỉnh sửa 
   - Khi sử dụng Led RGB không sử dụng được chức năng live expression trên stm32 
   - Hiện tạm thời không thể test thêm do Stlink đã bị hỏng , cần người hỗ trợ test thêm .

    
  
