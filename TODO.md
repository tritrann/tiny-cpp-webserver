# 🚀 Project Pipeline: My Tiny C++ HTTP Web Server

Lộ trình các bước triển khai dự án Web Server từ con số 0 bằng C++ và POSIX Sockets.

## 📍 Chặng 1: Thiết lập Hạ tầng mạng (TCP Server)
- [x] Tạo file cấu hình `main.cpp` và import các thư viện hệ thống (`<sys/socket.h>`, `<netinet/in.h>`).
- [ ] Khởi tạo con Welcome Socket gác cổng bằng hàm `socket()`.
- [ ] Cấu hình struct địa chỉ `sockaddr_in` (Gán IP và số phòng Port `8080`).
- [ ] Trói Socket gác cổng vào Port bằng hàm `bind()`.
- [ ] Chuyển Socket sang trạng thái mở tai lắng nghe bằng hàm `listen()`.

## 📍 Chặng 2: Tiếp đón Khách hàng & Hút dữ liệu (HTTP Request)
- [ ] Thiết lập vòng lặp vô tận `while(true)` để giữ Server liên tục chạy 24/7.
- [ ] Gọi hàm `accept()` chặn luồng để bắt tay 3 bước TCP ngầm và đẻ ra Connection Socket riêng.
- [ ] Khai báo mảng bộ đệm `char buffer[2048]` trong RAM để hứng dữ liệu.
- [ ] Gọi hàm `read()` / `recv()` để rút mớ bit thô HTTP Request từ Chrome đổ vào mảng buffer.
- [ ] In thông điệp Request ra Terminal bằng lệnh `std::cout` để kiểm tra nhãn bưu kiện.

## 📍 Chặng 3: Bộ não mổ xẻ thông tin (HTTP Parsing)
- [ ] Ép mảng dữ liệu thô sang kiểu chữ `std::string` của C++ để xử lý.
- [ ] Viết hàm tách chữ để bóc dòng lệnh đầu tiên (Request Line).
- [ ] Trích xuất phương thức (Kiểm tra xem có phải lệnh `GET` không) và đường dẫn file cần xin (URL).

## 📍 Chặng 4: Đóng gói Bưu kiện trả hàng (HTTP Response)
- [ ] Sử dụng thư viện `<fstream>` để lội vào ổ cứng đọc nội dung file giao diện tĩnh `index.html`.
- [ ] Tự nặn chiếc phong bì HTTP Response thô chuẩn luật (Gồm dòng trạng thái `200 OK`, nhãn `Content-Type: text/html` và dòng trống bắt buộc ở đáy thư).
- [ ] Đính kèm phần thịt nội dung file HTML vào sau dòng trống để tạo thành một khối dữ liệu thực thể (`Entity Body`).

## 📍 Chặng 5: Phóng hàng ra dây mạng & Tối ưu hóa (Dọn dẹp)
- [ ] Gọi hàm `write()` / `send()` để xả toàn bộ chiếc phong bì Response chạy ngược ra cổng truyền về cho Chrome.
- [ ] Gọi hàm `close()` để chặt đứt đường ống đàm thoại riêng nhằm giải phóng bộ nhớ RAM tức thời cho máy chủ.
- [ ] *[Nâng cấp nâng cao]* Viết thêm file `404.html` và nặn phong bì mã lỗi `404 Not Found` nếu người dùng gõ link bậy.
- [ ] *[Nâng cấp nâng cao]* Sử dụng thư viện `<thread>` biến Server thành đa luồng (Multi-threading) để xử lý nhiều khách cùng lúc.
