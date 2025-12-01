#include <stdio.h>
#include <string.h>

#define MAX 100
#define MAX_TRANS 500

typedef struct {
    char id[20];
    char name[50];
    char phone[15];
    float balance;
    int status; // 1: Hoat dong, 0: Khoa
} Account;

typedef struct {
    char fromId[20];
    char toId[20];
    float amount;
} Transaction;

// ================== DATA MAU =====================

Account list[MAX] = {
    {"1", "Chu Dinh A", "0901111111", 1500, 1},
    {"2", "Chu Dinh B", "0902222222", 3200, 1},
    {"3", "Chu Dinh C", "0903333333", 5000, 1},
    {"4", "Chu Dinh D", "0904444444", 7500, 1},
    {"5", "Chu Dinh E", "0905555555", 2000, 1},
    {"6", "Chu Dinh F", "0906666666", 1200, 1},
    {"7", "Chu Dinh G", "0907777777", 9800, 1},
    {"8", "Chu Dinh H", "0908888888", 2500, 1},
    {"9", "Chu Dinh I", "0909999999", 6400, 1},
    {"10", "Chu Dinh J", "0910000000", 8000, 1}
};

int count = 10;
Transaction history[MAX_TRANS];
int transCount = 0;

// ================== CHECK / UTILS =====================

int findIndexById(char id[]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].id, id) == 0)
            return i;
    }
    return -1;
}

int isDuplicateId(char id[]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].id, id) == 0) return 1;
    }
    return 0;
}

int isDuplicatePhone(char phone[], int ignoreIndex) {
    for (int i = 0; i < count; i++) {
        if (i != ignoreIndex && strcmp(list[i].phone, phone) == 0)
            return 1;
    }
    return 0;
}

void removeNewLine(char str[]) {
    str[strcspn(str, "\n")] = '\0';
}

// ================== CASE 1: THEM TAI KHOAN =====================
void addAccount() {
    Account acc;

    if (count >= MAX) {
        printf("Mang day, khong the them moi\n");
        return;
    }

    printf("\n=== THEM TAI KHOAN MOI ===\n");

    // ID
    do {
        printf("Nhap ID: ");
        fgets(acc.id, sizeof(acc.id), stdin);
        removeNewLine(acc.id);

        if (strlen(acc.id) == 0) {
            printf("ID khong duoc de trong\n");
            continue;
        }

        if (isDuplicateId(acc.id)) {
            printf("ID da ton tai\n");
            continue;
        }
        break;

    } while (1);

    // NAME
    do {
        printf("Nhap ho ten: ");
        fgets(acc.name, sizeof(acc.name), stdin);
        removeNewLine(acc.name);
        if (strlen(acc.name) == 0) {
            printf("Ho ten khong duoc de trong\n");
            continue;
        }
        break;
    } while (1);

    // PHONE
    do {
        printf("Nhap so dien thoai: ");
        fgets(acc.phone, sizeof(acc.phone), stdin);
        removeNewLine(acc.phone);

        if (strlen(acc.phone) == 0) {
            printf("SDT khong duoc de trong\n");
            continue;
        }
        if (isDuplicatePhone(acc.phone, -1)) {
            printf("SDT da ton tai!\n");
            continue;
        }
        break;

    } while (1);

    acc.balance = 0; // Mac dinh so du 0 
    acc.status = 1;

    list[count] = acc;
    count++;

    printf("Them tai khoan thanh cong!\n");
}

// ================== CASE 2: CAP NHAT =====================
void updateAccount() {
    char searchId[20];
    int index = -1;

    printf("\nNhap ID tai khoan can cap nhat: ");
    fgets(searchId, sizeof(searchId), stdin);
    removeNewLine(searchId);

    index = findIndexById(searchId);

    if (index == -1) {
        printf("Khong tim thay tai khoan\n");
        return;
    }

    printf("\n=== CAP NHAT ===\n");

    char newName[50];
    char newPhone[15];

    // Cap nhat ten  
    printf("Nhap ten moi: ");
    fgets(newName, sizeof(newName), stdin);
    removeNewLine(newName);
    if (strlen(newName) > 0)
        strcpy(list[index].name, newName);

    // Cap nhat sdt  
    do {
        printf("Nhap SDT moi: ");
        fgets(newPhone, sizeof(newPhone), stdin);
        removeNewLine(newPhone);

        if (strlen(newPhone) == 0) break;

        if (isDuplicatePhone(newPhone, index)) {
            printf("SDT da ton tai!\n");
            continue;
        }

        strcpy(list[index].phone, newPhone);
        break;

    } while (1);

    printf("Cap nhat thanh cong!\n");
}

// ================== CASE 3: KHOA / XOA =====================
void case3_DeleteOrLock() {
    char id[20];
    
    printf("\nNhap ID tai khoan: ");
    fgets(id, sizeof(id), stdin);
    removeNewLine(id);

    int index = findIndexById(id);
    if (index == -1) {
        printf("Khong tim thay tai khoan!\n");
        return;
    }

    printf("\n=== THONG TIN TAI KHOAN ===\n");
    printf("ID: %s\n", list[index].id);
    printf("Ten: %s\n", list[index].name);
    printf("So du: %.2f\n", list[index].balance);
    printf("Trang thai: %d\n\n", list[index].status);

    int option;
    printf("1. Khoa\n");
    printf("2. Xoa\n");
    printf("Nhap lua chon: ");
    scanf("%d", &option);

    int confirm;
    printf("Ban co chac chan? (1 = Co, 0 = Khong): ");
    scanf("%d", &confirm);
    getchar();

    if (confirm == 1) {
        if (option == 1) {
            list[index].status = 0;
            printf("Da khoa tai khoan!\n");
        }
        else if (option == 2) {
            for (int i = index; i < count - 1; i++) {
                list[i] = list[i + 1];
            }
            count--;
            printf("Da xoa tai khoan!\n");
        }
        else {
            printf("Lua chon khong hop le!\n");
        }
    } else {
        printf("Da huy thao tac!\n");
    }
}

// ================== CASE 4: TRA CUU =====================
void searchAccount() {
    char key[50];
    printf("\nNhap ID hoac ten: ");
    fgets(key, sizeof(key), stdin);
    removeNewLine(key);

    int found = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].id, key) == 0 ||
            strstr(list[i].name, key) != NULL) {
            
            if (found == 0) {
                printf("\nKET QUA TIM KIEM:\n");
                printf("+-----------+--------------------------+----------------+----------------+------------+\n");
                printf("| %-4s | %-24s | %-10s | %-10s | %-10s |\n", "ID", "HO TEN", "SDT", "SO DU", "TRANG THAI");
                printf("+-----------+--------------------------+----------------+----------------+------------+\n");
            }

            char statusStr[20];
            if (list[i].status == 1) strcpy(statusStr, "Hoat dong");
            else strcpy(statusStr, "Da khoa");

            printf("| %-4s | %-24s | %-10s | %10.2f | %-10s |\n",
                   list[i].id, list[i].name, list[i].phone, list[i].balance, statusStr);

            found = 1;
        }
    }

    if (found) {
        printf("+-----------+--------------------------+----------------+----------------+------------+\n");
    } else {
        printf("Khong tim thay ket qua nao!\n");
    }
}

// ================== CASE 5: PHAN TRANG =====================
void listPaging() {
    int pageSize;
    printf("\nNhap so dong moi trang: ");
    scanf("%d", &pageSize);
    getchar(); // Xoa bo dem

    if (pageSize <= 0) {
        printf("So dong phai lon hon 0!\n");
        return;
    }

    int totalPages = (count + pageSize - 1) / pageSize;
    if (count == 0) totalPages = 1; 
    
    int currentPage = 1;
    char navChoice;

    while (1) {
        int start = (currentPage - 1) * pageSize;
        int end = start + pageSize;
        if (end > count) end = count;

        printf("\n===== DANH SACH (Trang %d / %d) =====\n", currentPage, totalPages);
        
        
        printf("+-----+------+--------------------------+--------------+--------------+-------------+\n");
        printf("| %-3s | %-4s | %-24s | %-12s | %-12s | %-11s |\n", "STT", "ID", "HO TEN", "SDT", "SO DU", "TRANG THAI");
        printf("+-----+------+--------------------------+--------------+--------------+-------------+\n");

        for (int i = start; i < end; i++) {
            char statusStr[20];
            if (list[i].status == 1) strcpy(statusStr, "Hoat dong");
            else strcpy(statusStr, "Da khoa");

            // In tung dong du lieu co dinh dang
            printf("| %-3d | %-4s | %-24s | %-12s | %12.2f | %-11s |\n", 
                   i + 1, list[i].id, list[i].name, list[i].phone, list[i].balance, statusStr);
        }
        
        
        printf("+-----+------+--------------------------+--------------+--------------+-------------+\n");
        
        printf("(T) Trang truoc | (S) Trang sau | (E) Thoat: ");
        scanf(" %c", &navChoice); 

        if (navChoice == 'S' || navChoice == 's') {
            if (currentPage < totalPages) {
                currentPage++;
            } else {
                printf("\n>> Day la trang cuoi roi!\n");
            }
        }
        else if (navChoice == 'T' || navChoice == 't') {
            if (currentPage > 1) {
                currentPage--;
            } else {
                printf("\n>> Day la trang dau roi!\n");
            }
        }
        else if (navChoice == 'E' || navChoice == 'e') {
            break;
        }
        else {
            printf("Lua chon khong hop le!\n");
        }
    }
}

// ================== CASE 6: SAP XEP =====================
void sortList() {
    if (count == 0) {
        printf("Khong co du lieu!\n");
        return;
    }

    int choice;
    printf("\n1. Sap xep theo so du giam dan\n");
    printf("2. Sap xep theo ten A-Z\n");
    printf("Nhap lua chon: ");
    scanf("%d", &choice);
    getchar();

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (choice == 1) {
                if (list[i].balance < list[j].balance) {
                    Account temp = list[i];
                    list[i] = list[j];
                    list[j] = temp;
                }
            } else {
                if (strcmp(list[i].name, list[j].name) > 0) {
                    Account temp = list[i];
                    list[i] = list[j];
                    list[j] = temp;
                }
            }
        }
    }

    printf("Da sap xep xong!\n");
}

// ================== CASE 7: CHUYEN TIEN =====================
void transferMoney() {
    char from[20], to[20];
    float amt;

    // --- Nhap ID nguoi gui ---
    printf("\nNhap ID nguoi gui: ");
    fgets(from, sizeof(from), stdin);
    removeNewLine(from);
    
    // [MOI] Check ID rong
    if (strlen(from) == 0) {
        printf("Loi: ID nguoi gui khong duoc de trong!\n");
        return;
    }
    
    // --- Nhap ID nguoi nhan ---
    printf("Nhap ID nguoi nhan: ");
    fgets(to, sizeof(to), stdin);
    removeNewLine(to);

    //  Check ID rong
    if (strlen(to) == 0) {
        printf("Loi: ID nguoi nhan khong duoc de trong!\n");
        return;
    }

    // [VALIDATE] senderId khác receiverId
    if (strcmp(from, to) == 0) {
        printf("Loi: Khong duoc chuyen tien cho chinh minh!\n");
        return;
    }

    int senderIdx = findIndexById(from);
    int receiverIdx = findIndexById(to);

    // [VALIDATE] senderId và receiverId phai ton tai
    if (senderIdx == -1) {
        printf("Loi: ID nguoi gui (%s) khong ton tai!\n", from);
        return;
    }
    if (receiverIdx == -1) {
        printf("Loi: ID nguoi nhan (%s) khong ton tai!\n", to);
        return;
    }

    // [VALIDATE] accounts[sender].status == 1 (Check ca nguoi nhan de an toan)
    if (list[senderIdx].status == 0) {
        printf("Loi: Tai khoan nguoi gui dang bi KHOA, khong the thuc hien giao dich!\n");
        return;
    }
    if (list[receiverIdx].status == 0) {
        printf("Loi: Tai khoan nguoi nhan dang bi KHOA, khong the nhan tien!\n");
        return;
    }

    // --- Nhap so tien ---
    printf("Nhap so tien can chuyen: ");
    scanf("%f", &amt);
    getchar(); // Xoa bo dem

    // [VALIDATE] amount > 0
    if (amt <= 0) {
        printf("Loi: So tien chuyen phai lon hon 0!\n");
        return;
    }

    // [VALIDATE] amount <= accounts[sender].balance
    if (amt > list[senderIdx].balance) {
        printf("Loi: So du khong du (Du hien tai: %.2f)!\n", list[senderIdx].balance);
        return;
    }

    // --- THUC HIEN GIAO DICH ---
    list[senderIdx].balance -= amt;
    list[receiverIdx].balance += amt;

    // Luu lich su
    strcpy(history[transCount].fromId, from);
    strcpy(history[transCount].toId, to);
    history[transCount].amount = amt;
    transCount++;

    printf("Chuyen khoan thanh cong! So du con lai: %.2f\n", list[senderIdx].balance);
}

// ================== CASE 8: LICH SU =====================
void showHistory() {
    // [VALIDATE] Kiem tra du lieu: Neu he thong chua co giao dich nao
    if (transCount == 0) {
        printf("\nHe thong chua co giao dich nao!\n");
        return;
    }

    char id[20];
    printf("\nNhap ID can xem lich su: ");
    fgets(id, sizeof(id), stdin);
    removeNewLine(id);
    
    if (strlen(id) == 0) {
        printf("Loi: ID khong duoc de trong!\n");
        return;
    }

    // [VALIDATE] Kiem tra ton tai: targetId phai co trong danh sach
    int idx = findIndexById(id);
    if (idx == -1) {
        printf("Loi: Tai khoan '%s' khong ton tai!\n", id);
        return;
    }

    int found = 0;
    
    printf("\nLICH SU GIAO DICH CUA: %s (ID: %s)\n", list[idx].name, list[idx].id);
    printf("+------------------+--------------------+--------------------+\n");
    printf("| %-16s | %-18s | %-18s |\n", "LOAI GIAO DICH", "ID NGUOI GD", "SO TIEN");
    printf("+------------------+--------------------+--------------------+\n");

    for (int i = 0; i < transCount; i++) {
        // Giao dich gui tien (OUT)
        if (strcmp(history[i].fromId, id) == 0) {
            printf("| %-16s | %-18s | %15.2f (-)|\n", "CHUYEN DI", history[i].toId, history[i].amount);
            found = 1;
        }
        // Giao dich nhan tien (IN)
        else if (strcmp(history[i].toId, id) == 0) {
            printf("| %-16s | %-18s | %15.2f (+)|\n", "NHAN DUOC", history[i].fromId, history[i].amount);
            found = 1;
        }
    }

    if (!found) {
        printf("| %-58s |\n", "Tai khoan nay chua phat sinh giao dich nao.");
    }
    
    printf("+------------------+--------------------+--------------------+\n");
}

// ================== MENU =====================
void showMenu() {
    printf("\n===== QUAN LY TAI KHOAN =====\n");
    printf("1. Them tai khoan moi\n");
    printf("2. Cap nhat thong tin tai khoan\n");
    printf("3. Quan ly tai khoan (Khoa / Xoa)\n");
    printf("4. Tra cuu tai khoan\n");
    printf("5. Danh sach tai khoan (Phan trang)\n");
    printf("6. Sap xep danh sach\n");
    printf("7. Giao dich chuyen khoan\n");
    printf("8. Lich su giao dich\n");
    printf("9. Thoat\n");
    printf("===============================\n");
    printf("Nhap lua chon: ");
}

// ================== MAIN =====================
int main() {
    int choice;

    do {
        showMenu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addAccount(); break;
            case 2: updateAccount(); break;
            case 3: case3_DeleteOrLock(); break;
            case 4: searchAccount(); break;
            case 5: listPaging(); break;
            case 6: sortList(); break;
            case 7: transferMoney(); break;
            case 8: showHistory(); break;
            case 9: printf("Thoat chuong trinh...\n"); break;
            default: printf("Lua chon khong hop le!\n");
        }

    } while (choice != 9);

    return 0;
}
