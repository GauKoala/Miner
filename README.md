# Giới thiệu:
- Game dò mìn
- Viết bằng ngôn ngữ C++, dùng thư viên SDL2
  Ngôn ngữ: C++ - SDL2.
# Luật chơi
Trò chơi minesweeper cơ bản 
- Mục tiêu là mở tất cả các ô trống trong bảng mà không ấn vào các ô chứa bom.
- Mỗi ô trong bảng có thể là một trong ba loại.
-  Ô trống: không chứa bom, khi mở khiến các ô trống và ô số xung quang mở theo.
-  Ô chứa bom: nếu mở phải ô này, trò chơi kết thúc.
-  Ô chứa số: cho biết có bao nhiêu ô chứa bom xung quanh ô đó (từ 0 đến 8).
-  Người chơi mở một ô bằng cách nhấp vào đó. Nếu ô đó là ô trống, nó sẽ mở và hiển thị các ô trống và ô số xung quang; nếu ô đó chứa số, ô đó sẽ hiển thị số bom, nếu ô đó chứa bom trò chơi kết thúc.
-  Người chơi có thể đặt một cờ trên ô mà họ cho rằng chứa bom để đánh dấu.
-  Trò chơi kết thúc khi người chơi mở tất cả các ô không chứa bom hoặc khi họ mở một ô chứa bom.
-   Mục tiêu cuối cùng là mở tất cả các ô không chứa bom mà không chạm vào bất kỳ ô nào chứa bom.
# Cách chơi:
- PLay: Bắt đầu chơi
- Quit: Thoát game
- Easy, Medium, Hard: Độ khó
- Chuột trái: Mở ô
- Chuột phải: Đánh dấu cờ
# Sử dụng: 
- IDE: Code:Blocks 20.3
- Thư viện: SDL2-2.30.2, SDL2_image-2.8.2, SDL2_ttf-2.22.0, SDL2_mixer-2.8.0
# Tài liệu tham khảo:
- https://lazyfoo.net/tutorials/SDL/
- https://www.youtube.com/watch?v=RmpSnfVZZmI





