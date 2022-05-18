# GameSDL2_Project : KILL MONSTER 1.0

1. Hướng dẫn cài đặt và sử dụng
 - Truy cập vào đường dẫn : https://github.com/lamtrongvinh/GameSDL2_Project
 - Vào mục "Code" -> Nhấn coppy đường dẫn (VD: https://github.com/lamtrongvinh/GameSDL2_Project.git )
 - Về máy cá nhân, mở terminal lên di chuyển đến nơi cần chứa game
 - Gõ câu lệnh : git clone https://github.com/lamtrongvinh/GameSDL2_Project.git
 ==> Thư mục chứa game đã được tải về máy.
 - Mở Visual Studio, CodeBlock, VSCODE đã cài đặt thư viện SDL2 (SDL_mixer, SDL_ttf, SDL_image) và có thể chơi thử game.

2. Mô tả chung về trò chơi
 - Người chơi sẽ nhập vai vào một nhân vật chiến binh , được giao nhiệm vụ đi đến hết bản đồ và thu thập kim cương.
 - Trong quá trình di chuyển trên bản đồ, chiến binh gặp nhưng chướng ngại vật là những quái vật. Để tiêu diệt được quái vật thì chiến binh sẽ dùng súng của mình để bắn chúng và ngược lại nếu chiến binh va chạm với quái vật, đạn của quái vật và rơi xuống vực thì máu của chiến binh sẽ bị trừ đi 1.
 - Nếu máu về 0, chiến binh sẽ chết còn khi chiến binh di được đến cuối map thì sẽ giành được chiến thắng.
 - Trong quá trình di chuyển chiến binh sẽ tích lũy điểm số của mình bằng cách đó là :
    + Nếu hạ gục được 1 quái vật sẽ được : +5 điểm.
    + Ăn được item kim cương sẽ được : +10 điểm.
    + Nếu bị chết 1 lần sẽ bị : -5 điểm.

3. Mô tả các chức năng đã cài đặt
 - Khi vào game chúng ta sẽ có 2 lựa chọn : "Join Game" hoặc "Quit". Click chuột trái để vào game hoặc thoát.
 - Điều khiển nhân vật chiến binh :
    + UP (RightMouse) : Nhảy lên.
    + Down : Đi Xuống.
    + Left : Di chuyển sang trái.
    + Right : Di chuyển sang phát.
    + LeftMouse : Bắn súng.
 - Nhạc nền được phát khi vào game.
 - Khi bắn sẽ có âm thanh súng.
 - Khi ăn được item kim cương sẽ có âm thanh .
 - Khi bị trừ 1 máu sẽ có âm thanh.
 - Khi máu về 0 sẽ có âm thanh game_over.
 - Khi đến cuối map sẽ có âm thanh you_win.
 - Khi thất bại và chiến thắng sẽ có 2 lựa chọn đó là "Play Again" hoặc "Quit".

 - Link youtube  : 

 4. Các kỹ thuật lập trình được sử dụng trong chương trình
 - Sử dụng các class, struct để quản lí đối tượng.
 - Sử dụng con trỏ.
 - Tách file để dễ quản lí thông tin.
 5. Kết luận
 - Sau này sẽ cố gắng phát triển thêm những tính năng khác như chọn nhân vật, tạo ra những quái vật boss, chọn map ....
 - Khi hoàn thành được bài tập lớn này giúp cho bản thân phát triển được kĩ năng lập trình, khả năng quản lí những đối tượng cũng như thuật toán tốt hơn.
 
