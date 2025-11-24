#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char id[20];
    char name[50];
    char phone[15];
    float balance;
} Account;

Account list[MAX];
int count = 0;

void addAccount() {
    Account acc;

    if (count >= MAX) {
        printf("Mang day, khong the them moi!\n");
        return;
    }

    printf("\n=== THEM TAI KHOAN MOI ===\n");

    printf("Nhap ID: ");
    scanf("%s", acc.id);

    printf("Nhap ho ten: ");
    scanf("%s", acc.name);

    printf("Nhap so dien thoai: ");
    scanf("%s", acc.phone);

    printf("Nhap so du ban dau: ");
    scanf("%f", &acc.balance);

    list[count] = acc;
    count++;

    printf("=> Them tai khoan thanh cong!\n");
}

void updateAccount() {
    char searchId[20];
    int i;

    printf("\nNhap ID tai khoan can cap nhat: ");
    scanf("%s", searchId);

    for (i = 0; i < count; i++) {
        if (strcmp(list[i].id, searchId) == 0) {
            printf("\n=== CAP NHAT THONG TIN ===\n");

            printf("Nhap ten moi: ");
            scanf("%s", list[i].name);

            printf("Nhap so dien thoai moi: ");
            scanf("%s", list[i].phone);

            printf("Nhap so du moi: ");
            scanf("%f", &list[i].balance);

            printf("=> Cap nhat thanh cong!\n");
            return;
        }
    }

    printf("=> Khong tim thay tai khoan!\n");
}

void showMenu() {
    printf("\n===== QUAN LY TAI KHOAN =====\n");
    printf("1. Them tai khoan moi\n");
    printf("2. Cap nhat thong tin tai khoan\n");
    printf("3. Quan ly trang thai (Khoa / Xoa)\n");
    printf("4. Tra cuu tai khoan (Tim kiem)\n");
    printf("5. Danh sach tai khoan\n");
    printf("6. Sap xep danh sach\n");
    printf("7. Giao dich chuyen khoan\n");
    printf("8. Lich su giao dich\n");
    printf("0. Thoat\n");
    printf("================================\n");
    printf("Nhap lua chon: ");
}

int main() {
    int choice;

    do {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addAccount();
                break;
            case 2:
                updateAccount();
                break;
            case 0:
                printf("Thoat chuong trinh...\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }

    } while (choice != 0);

    return 0;
}

