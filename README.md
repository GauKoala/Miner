#
  Ngôn ngữ: C++ - SDL2.
  
  Phần mềm sử dụng: [CodeBlock]
# miner
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
- Có 3 mức độ:
   + Dễ: Bảng 9 x 9, 10 bom.
   + Trung bình: Bảng 16 x 16, 40 bom.
   + Khó: Bảng 30 x 16 , 99 bom.
- Chuột phải: cắm cờ
- Chuột trái: mở ô





