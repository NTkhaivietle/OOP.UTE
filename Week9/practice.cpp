#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_FOODS = 100;
const int MAX_ORDERS = 100;

// -------------------------------------------------------------
// 1. KHAI BÁO CẤU TRÚC DỮ LIỆU (STRUCTS)
// -------------------------------------------------------------

// Cấu trúc Món ăn
struct Food {
    string id;        // Mã món
    string name;      // Tên món
    double price;     // Đơn giá (VND)
    int quantity;     // Số lượng tồn kho
};

// Cấu trúc Đơn hàng
struct Order {
    string id;           // Mã đơn hàng
    string customerName; // Tên khách hàng
    string address;      // Địa chỉ giao hàng
    Food food;           // Thông tin món ăn đặt
    int quantity;        // Số lượng đặt
    string status;       // Trạng thái: "Đang xử lý", "Đã giao", "Đã hủy"
};

// Cấu trúc Cửa hàng (Chứa toàn bộ dữ liệu quản lý)
struct Restaurant {
    string name;         // Tên cửa hàng
    string address;      // Địa chỉ
    string phone;        // Số điện thoại
    
    Food foods[MAX_FOODS];
    int foodCount = 0;
    
    Order orders[MAX_ORDERS];
    int orderCount = 0;
};

// -------------------------------------------------------------
// 2. KHAI BÁO CÁC HÀM NGHỆU VỤ
// -------------------------------------------------------------

void khoiTaoDuLieuMau(Restaurant &res);
void nhapThongTinCuaHang(Restaurant &res);
void hienThiThongTinCuaHang(const Restaurant &res);

// Quản lý món ăn
void themMonAn(Restaurant &res);
void hienThiDanhSachMonAn(const Restaurant &res);
int timKiemMonAnTheoMa(const Restaurant &res, const string &id);
void timKiemMonAn(const Restaurant &res);
void capNhatMonAn(Restaurant &res);

// Quản lý đơn hàng
void taoDonHangMoi(Restaurant &res);
void hienThiDanhSachDonHang(const Restaurant &res);
int timKiemDonHangTheoMa(const Restaurant &res, const string &id);
void timKiemDonHang(const Restaurant &res);
void capNhatTrangThaiDonHang(Restaurant &res);
void thongKeDoanhThu(const Restaurant &res);

// -------------------------------------------------------------
// 3. HÀM MAIN (MENU ĐIỀU KHIỂN)
// -------------------------------------------------------------

int main() {
    Restaurant res;
    
    // Nạp dữ liệu mẫu ban đầu để tiện kiểm thử
    khoiTaoDuLieuMau(res);

    int choice;
    do {
        cout << "\n==================================================\n";
        cout << "   CHƯƠNG TRÌNH QUẢN LÝ CỬA HÀNG GIAO ĐỒ ĂN (C++)\n";
        cout << "==================================================\n";
        cout << "1. Nhập / Cập nhật thông tin cửa hàng\n";
        cout << "2. Thêm món ăn mới vào Menu\n";
        cout << "3. Hiển thị danh sách món ăn\n";
        cout << "4. Tìm kiếm món ăn theo Mã hoặc Tên\n";
        cout << "5. Cập nhật thông tin món ăn (Đơn giá / Tồn kho)\n";
        cout << "6. Tạo đơn hàng mới\n";
        cout << "7. Hiển thị danh sách tất cả đơn hàng\n";
        cout << "8. Tìm kiếm đơn hàng theo Mã đơn\n";
        cout << "9. Cập nhật trạng thái đơn hàng (Đã giao / Hủy...)\n";
        cout << "10. Thống kê tổng doanh thu (Các đơn đã giao)\n";
        cout << "11. Xem thông tin cửa hàng\n";
        cout << "0. Thoát chương trình\n";
        cout << "--------------------------------------------------\n";
        cout << "Lựa chọn của bạn (0-11): ";
        cin >> choice;
        cin.ignore(); // Xóa bộ nhớ đệm sau cin

        switch (choice) {
            case 1:
                nhapThongTinCuaHang(res);
                break;
            case 2:
                themMonAn(res);
                break;
            case 3:
                hienThiDanhSachMonAn(res);
                break;
            case 4:
                timKiemMonAn(res);
                break;
            case 5:
                capNhatMonAn(res);
                break;
            case 6:
                taoDonHangMoi(res);
                break;
            case 7:
                hienThiDanhSachDonHang(res);
                break;
            case 8:
                timKiemDonHang(res);
                break;
            case 9:
                capNhatTrangThaiDonHang(res);
                break;
            case 10:
                thongKeDoanhThu(res);
                break;
            case 11:
                hienThiThongTinCuaHang(res);
                break;
            case 0:
                cout << "\nCảm ơn bạn đã sử dụng chương trình! Tạm biệt.\n";
                break;
            default:
                cout << "\nLựa chọn không hợp lệ! Vui lòng chọn lại từ 0 đến 11.\n";
        }
    } while (choice != 0);

    return 0;
}

// -------------------------------------------------------------
// 4. CHI TIẾT CÁC HÀM XỬ LÝ
// -------------------------------------------------------------

// Khởi tạo sẵn một số dữ liệu mẫu
void khoiTaoDuLieuMau(Restaurant &res) {
    res.name = "Bếp Việt Delivery";
    res.address = "123 Đường Nguyễn Huệ, Q.1, TP.HCM";
    res.phone = "0909123456";

    // Món ăn mẫu
    res.foods[0] = {"F01", "Cơm Tấm Sườn Bì Chả", 45000, 30};
    res.foods[1] = {"F02", "Bún Bò Huế Đặc Biệt", 55000, 20};
    res.foods[2] = {"F03", "Trà Sữa Thái Xanh", 25000, 50};
    res.foodCount = 3;

    // Đơn hàng mẫu
    res.orders[0] = {"ORD01", "Nguyễn Văn A", "45 Lê Lợi, Q.1", res.foods[0], 2, "Đã giao"};
    res.orders[1] = {"ORD02", "Trần Thị B", "12 Nam Kỳ Khởi Nghĩa", res.foods[1], 1, "Đang xử lý"};
    res.orderCount = 2;
}

// Chức năng 1: Nhập thông tin cửa hàng
void nhapThongTinCuaHang(Restaurant &res) {
    cout << "\n--- NHẬP THÔNG TIN CỬA HÀNG ---\n";
    cout << "Nhập tên cửa hàng: ";
    getline(cin, res.name);
    cout << "Nhập địa chỉ: ";
    getline(cin, res.address);
    cout << "Nhập số điện thoại: ";
    getline(cin, res.phone);
    cout << "=> Cập nhật thông tin cửa hàng thành công!\n";
}

// Xem thông tin cửa hàng
void hienThiThongTinCuaHang(const Restaurant &res) {
    cout << "\n=========================================\n";
    cout << "THÔNG TIN CỬA HÀNG\n";
    cout << "=========================================\n";
    cout << "Tên cửa hàng : " << res.name << "\n";
    cout << "Địa chỉ      : " << res.address << "\n";
    cout << "Hotline      : " << res.phone << "\n";
    cout << "Tổng số món  : " << res.foodCount << "\n";
    cout << "Tổng số đơn  : " << res.orderCount << "\n";
    cout << "=========================================\n";
}

// Chức năng 2: Thêm món ăn mới
void themMonAn(Restaurant &res) {
    if (res.foodCount >= MAX_FOODS) {
        cout << "\nDanh sách món ăn đã đầy! Không thể thêm nữa.\n";
        return;
    }

    Food f;
    cout << "\n--- THÊM MÓN ĂN MỚI ---\n";
    cout << "Nhập mã món ăn (ví dụ: F04): ";
    getline(cin, f.id);

    // Kiểm tra trùng mã món
    if (timKiemMonAnTheoMa(res, f.id) != -1) {
        cout << "Lỗi: Mã món ăn '" << f.id << "' đã tồn tại trong hệ thống!\n";
        return;
    }

    cout << "Nhập tên món ăn: ";
    getline(cin, f.name);
    cout << "Nhập đơn giá (VND): ";
    cin >> f.price;
    cout << "Nhập số lượng tồn kho: ";
    cin >> f.quantity;
    cin.ignore();

    res.foods[res.foodCount] = f;
    res.foodCount++;

    cout << "=> Thêm món ăn '" << f.name << "' thành công!\n";
}

// Chức năng 3: Hiển thị danh sách món ăn
void hienThiDanhSachMonAn(const Restaurant &res) {
    cout << "\n====================================================================\n";
    cout << "                      DANH SÁCH MÓN ĂN (MENU)                       \n";
    cout << "====================================================================\n";
    cout << left << setw(10) << "Mã Món"
         << setw(30) << "Tên Món Ăn"
         << setw(15) << "Đơn Giá (VND)"
         << setw(12) << "Tồn Kho" << "\n";
    cout << "--------------------------------------------------------------------\n";

    if (res.foodCount == 0) {
        cout << "Chưa có món ăn nào trong danh sách.\n";
    } else {
        for (int i = 0; i < res.foodCount; i++) {
            cout << left << setw(10) << res.foods[i].id
                 << setw(30) << res.foods[i].name
                 << setw(15) << fixed << setprecision(0) << res.foods[i].price
                 << setw(12) << res.foods[i].quantity << "\n";
        }
    }
    cout << "====================================================================\n";
}

// Tìm index món ăn theo Mã món
int timKiemMonAnTheoMa(const Restaurant &res, const string &id) {
    for (int i = 0; i < res.foodCount; i++) {
        if (res.foods[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Chức năng 4: Tìm kiếm món ăn theo mã hoặc tên
void timKiemMonAn(const Restaurant &res) {
    cout << "\n--- TÌM KIẾM MÓN ĂN ---\n";
    cout << "Nhập mã món hoặc từ khóa tên món: ";
    string keyword;
    getline(cin, keyword);

    bool found = false;
    cout << "\nKết quả tìm kiếm cho '" << keyword << "':\n";
    cout << left << setw(10) << "Mã Món"
         << setw(30) << "Tên Món Ăn"
         << setw(15) << "Đơn Giá (VND)"
         << setw(12) << "Tồn Kho" << "\n";
    cout << "--------------------------------------------------------------------\n";

    for (int i = 0; i < res.foodCount; i++) {
        if (res.foods[i].id == keyword || res.foods[i].name.find(keyword) != string::npos) {
            cout << left << setw(10) << res.foods[i].id
                 << setw(30) << res.foods[i].name
                 << setw(15) << fixed << setprecision(0) << res.foods[i].price
                 << setw(12) << res.foods[i].quantity << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "Không tìm thấy món ăn phù hợp.\n";
    }
}

// Chức năng 5: Cập nhật thông tin món ăn
void capNhatMonAn(Restaurant &res) {
    cout << "\n--- CẬP NHẬT THÔNG TIN MÓN ĂN ---\n";
    cout << "Nhập mã món ăn cần cập nhật: ";
    string id;
    getline(cin, id);

    int idx = timKiemMonAnTheoMa(res, id);
    if (idx == -1) {
        cout << "Không tìm thấy món ăn có mã: " << id << "\n";
        return;
    }

    cout << "Đang cập nhật món: " << res.foods[idx].name << "\n";
    cout << "1. Đổi đơn giá (Hiện tại: " << fixed << setprecision(0) << res.foods[idx].price << " VND)\n";
    cout << "2. Cập nhật số lượng tồn kho (Hiện tại: " << res.foods[idx].quantity << ")\n";
    cout << "3. Cập nhật cả hai\n";
    cout << "Lựa chọn: ";
    int subChoice;
    cin >> subChoice;

    if (subChoice == 1 || subChoice == 3) {
        cout << "Nhập đơn giá mới: ";
        cin >> res.foods[idx].price;
    }
    if (subChoice == 2 || subChoice == 3) {
        cout << "Nhập số lượng tồn kho mới: ";
        cin >> res.foods[idx].quantity;
    }
    cin.ignore();

    cout << "=> Cập nhật món ăn thành công!\n";
}

// Chức năng 6, 7, 8: Tạo đơn hàng mới
void taoDonHangMoi(Restaurant &res) {
    if (res.orderCount >= MAX_ORDERS) {
        cout << "\nDanh sách đơn hàng đã đầy!\n";
        return;
    }

    cout << "\n--- TẠO ĐƠN HÀNG MỚI ---\n";
    
    // Hiển thị Menu trước để khách/nhân viên chọn
    hienThiDanhSachMonAn(res);

    cout << "Nhập mã món ăn khách chọn đặt: ";
    string foodId;
    getline(cin, foodId);

    int foodIdx = timKiemMonAnTheoMa(res, foodId);
    if (foodIdx == -1) {
        cout << "Lỗi: Mã món ăn không tồn tại!\n";
        return;
    }

    cout << "Nhập số lượng đặt: ";
    int qty;
    cin >> qty;
    cin.ignore();

    // Chức năng 7 (slide): Kiểm tra món ăn có đủ số lượng không
    if (qty <= 0) {
        cout << "Số lượng đặt phải lớn hơn 0!\n";
        return;
    }
    if (qty > res.foods[foodIdx].quantity) {
        cout << "Lỗi: Số lượng tồn kho không đủ! (Còn lại: " << res.foods[foodIdx].quantity << ")\n";
        return;
    }

    Order ord;
    cout << "Nhập mã đơn hàng (ví dụ: ORD03): ";
    getline(cin, ord.id);

    if (timKiemDonHangTheoMa(res, ord.id) != -1) {
        cout << "Lỗi: Mã đơn hàng đã tồn tại!\n";
        return;
    }

    cout << "Nhập tên khách hàng: ";
    getline(cin, ord.customerName);
    cout << "Nhập địa chỉ giao hàng: ";
    getline(cin, ord.address);

    ord.food = res.foods[foodIdx];
    ord.quantity = qty;
    ord.status = "Đang xử lý";

    // Trừ bớt số lượng tồn kho
    res.foods[foodIdx].quantity -= qty;

    // Chức năng 8 (slide): Tính tổng tiền đơn hàng
    double totalAmount = ord.food.price * ord.quantity;

    res.orders[res.orderCount] = ord;
    res.orderCount++;

    cout << "\n-----------------------------------------\n";
    cout << "=> THÊM ĐƠN HÀNG THÀNH CÔNG!\n";
    cout << "Tổng tiền thanh toán: " << fixed << setprecision(0) << totalAmount << " VND\n";
    cout << "Trạng thái đơn: " << ord.status << "\n";
    cout << "-----------------------------------------\n";
}

// Chức năng 9: Hiển thị danh sách tất cả các đơn hàng
void hienThiDanhSachDonHang(const Restaurant &res) {
    cout << "\n===============================================================================================\n";
    cout << "                                     DANH SÁCH ĐƠN HÀNG                                       \n";
    cout << "===============================================================================================\n";
    cout << left << setw(10) << "Mã Đơn"
         << setw(20) << "Tên Khách Hàng"
         << setw(22) << "Món Đặt"
         << setw(8)  << "SL"
         << setw(16) << "Tổng Tiền (VND)"
         << setw(15) << "Trạng Thái" << "\n";
    cout << "-----------------------------------------------------------------------------------------------\n";

    if (res.orderCount == 0) {
        cout << "Chưa có đơn hàng nào.\n";
    } else {
        for (int i = 0; i < res.orderCount; i++) {
            double total = res.orders[i].food.price * res.orders[i].quantity;
            cout << left << setw(10) << res.orders[i].id
                 << setw(20) << res.orders[i].customerName
                 << setw(22) << res.orders[i].food.name
                 << setw(8)  << res.orders[i].quantity
                 << setw(16) << fixed << setprecision(0) << total
                 << setw(15) << res.orders[i].status << "\n";
        }
    }
    cout << "===============================================================================================\n";
}

// Tìm index đơn hàng theo mã
int timKiemDonHangTheoMa(const Restaurant &res, const string &id) {
    for (int i = 0; i < res.orderCount; i++) {
        if (res.orders[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Chức năng 10: Tìm đơn hàng theo mã
void timKiemDonHang(const Restaurant &res) {
    cout << "\n--- TÌM KIẾM ĐƠN HÀNG --- \n";
    cout << "Nhập mã đơn hàng cần tìm: ";
    string id;
    getline(cin, id);

    int idx = timKiemDonHangTheoMa(res, id);
    if (idx == -1) {
        cout << "Không tìm thấy đơn hàng mã: " << id << "\n";
        return;
    }

    const Order &ord = res.orders[idx];
    double total = ord.food.price * ord.quantity;

    cout << "\n-----------------------------------------\n";
    cout << "CHI TIẾT ĐƠN HÀNG [" << ord.id << "]\n";
    cout << "-----------------------------------------\n";
    cout << "Khách hàng   : " << ord.customerName << "\n";
    cout << "Địa chỉ giao : " << ord.address << "\n";
    cout << "Món đã đặt   : " << ord.food.name << " (Đơn giá: " << fixed << setprecision(0) << ord.food.price << " VND)\n";
    cout << "Số lượng đặt : " << ord.quantity << "\n";
    cout << "Thành tiền   : " << total << " VND\n";
    cout << "Trạng thái   : " << ord.status << "\n";
    cout << "-----------------------------------------\n";
}

// Chức năng 11: Cập nhật trạng thái đơn hàng
void capNhatTrangThaiDonHang(Restaurant &res) {
    cout << "\n--- CẬP NHẬT TRẠNG THÁI ĐƠN HÀNG ---\n";
    cout << "Nhập mã đơn hàng: ";
    string id;
    getline(cin, id);

    int idx = timKiemDonHangTheoMa(res, id);
    if (idx == -1) {
        cout << "Không tìm thấy đơn hàng mã: " << id << "\n";
        return;
    }

    cout << "Đơn hàng hiện tại đang ở trạng thái: '" << res.orders[idx].status << "'\n";
    cout << "Chọn trạng thái mới:\n";
    cout << "1. Đang xử lý\n";
    cout << "2. Đã giao (Giao thành công)\n";
    cout << "3. Đã hủy\n";
    cout << "Lựa chọn: ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        res.orders[idx].status = "Đang xử lý";
    } else if (choice == 2) {
        res.orders[idx].status = "Đã giao";
    } else if (choice == 3) {
        // Nếu hủy đơn hàng, hoàn trả lại số lượng tồn kho cho món ăn
        if (res.orders[idx].status != "Đã hủy") {
            int foodIdx = timKiemMonAnTheoMa(res, res.orders[idx].food.id);
            if (foodIdx != -1) {
                res.foods[foodIdx].quantity += res.orders[idx].quantity;
            }
        }
        res.orders[idx].status = "Đã hủy";
    } else {
        cout << "Lựa chọn không hợp lệ!\n";
        return;
    }

    cout << "=> Đã cập nhật trạng thái đơn hàng '" << id << "' thành: " << res.orders[idx].status << "\n";
}

// Chức năng 12: Thống kê tổng doanh thu của các đơn đã hoàn thành ("Đã giao")
void thongKeDoanhThu(const Restaurant &res) {
    double totalRevenue = 0;
    int deliveredCount = 0;

    for (int i = 0; i < res.orderCount; i++) {
        if (res.orders[i].status == "Đã giao") {
            totalRevenue += res.orders[i].food.price * res.orders[i].quantity;
            deliveredCount++;
        }
    }

    cout << "\n==================================================\n";
    cout << "               THỐNG KÊ DOANH THU                 \n";
    cout << "==================================================\n";
    cout << "Tổng số đơn đã hoàn thành (Đã giao) : " << deliveredCount << " / " << res.orderCount << " đơn\n";
    cout << "TỔNG DOANH THU THỰC TẾ               : " << fixed << setprecision(0) << totalRevenue << " VND\n";
    cout << "==================================================\n";
}