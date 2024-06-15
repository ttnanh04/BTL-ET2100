
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char malop[10];
    char thu;
    char bd, kt;
    char diadiem[10];
    char magv[5][10];
} lop;

struct nodelh {
    lop lh;
    nodelh *next;
};
typedef struct nodelh *pnodelh;
typedef struct nodelh *lllop;

typedef struct {
    char mahp[10];
    char tenhp[50];
    lllop dslop;
} hocphan;

struct nodehp {
    hocphan hp;
    nodehp *next;
};
typedef struct nodehp *pnodehp;
typedef struct nodehp *llhp;

struct nodelk {
    pnodehp hp;
    char malop[10];
    nodelk *next;
};
typedef struct nodelk *pnodelk;
typedef struct nodelk *lllk;

typedef struct {
    char magv[10];
    char tengv[50];
    lllk lop;
} giangvien;

struct nodegv {
    giangvien gv;
    nodegv *next;
};
typedef struct nodegv *pnodegv;
typedef struct nodegv *llgv;



//  hàm xóa ID cua gv ra khoi 1 lop
void xoa_gv_khoi_lop(llgv ds_gv, const char* magv, const char* malop) {
    pnodegv current_gv = ds_gv;
    while (current_gv != NULL) {
        if (strcmp(current_gv->gv.magv, magv) == 0) {
            lllk current_lk = current_gv->gv.lop;
            lllk prev_lk = NULL;

            while (current_lk != NULL) {
                if (strcmp(current_lk->malop, malop) == 0) {
                    // xóa ID cua gv ra khoi lop
                    pnodelh current_lh = current_lk->hp->hp.dslop;
                    while (current_lh != NULL) {
                        for (int i = 0; i < 5; ++i) {
                            if (strcmp(current_lh->lh.magv[i], magv) == 0) {
                                // dich chuyen các ID cua gv tiep theo sang trái 1 vi trí
                                for (int j = i; j < 4; ++j) {
                                    strcpy(current_lh->lh.magv[j], current_lh->lh.magv[j + 1]);
                                }
                                // thuc hien xóa
                                strcpy(current_lh->lh.magv[4], "");
                                printf("Removed teacher ID %s from class %s\n", magv, malop);
                            }
                        }
                        current_lh = current_lh->next;
                    }

                    // xóa thông tin cua lop ra khoi thông tin cua gv
                    if (prev_lk == NULL) {
                        current_gv->gv.lop = current_lk->next;
                    } else {
                        prev_lk->next = current_lk->next;
                    }
                    free(current_lk);
                    printf("Removed class ID %s from teacher %s's record\n", malop, magv);
                    return;
                }
                prev_lk = current_lk;
                current_lk = current_lk->next;
            }
        }
        current_gv = current_gv->next;
    }
    printf("Teacher or class not found\n");
}

// xóa gv ra khoi danh sách liên ket gv
void xoa_gv(llgv* ds_gv, const char* magv) {
    pnodegv current_gv = *ds_gv;
    pnodegv prev_gv = NULL;
    
    while (current_gv != NULL) {
        if (strcmp(current_gv->gv.magv, magv) == 0) {
            if (prev_gv == NULL) {
                *ds_gv = current_gv->next;  // Gv can loai bo  dau danh sách
            } else {
                prev_gv->next = current_gv->next;
            }
            // Giai phong bo nho 
            pnodelk current_lk = current_gv->gv.lop;
            while (current_lk != NULL) {
                pnodelk temp_lk = current_lk;
                current_lk = current_lk->next;
                free(temp_lk);
            }
            free(current_gv);
            printf("Teacher ID %s has been removed from the list\n", magv);
            return;
        }
        prev_gv = current_gv;
        current_gv = current_gv->next;
    }
    printf("Teacher not found\n");
}

int main() {
    // Example data setup
    
    // Create an example class
    lop lop1 = { "L01", '2', 8, 10, "Room101", { "GV01" } };
    pnodelh nodeLop1 = new nodelh;
    nodeLop1->lh = lop1;
    nodeLop1->next = NULL;
    
    // Create an example hocphan
    hocphan hp1 = { "HP01", "Hoc Phan 1", nodeLop1 };
    pnodehp nodeHp1 = new nodehp;
    nodeHp1->hp = hp1;
    nodeHp1->next = NULL;

    // Link hocphan to nodelk
    pnodelk nodeLk1 = new nodelk;
    strcpy(nodeLk1->malop, "L01");
    nodeLk1->hp = nodeHp1;
    nodeLk1->next = NULL;

    // Create an example teacher
    giangvien gv1 = { "GV01", "Nguyen Van A", nodeLk1 };
    pnodegv nodeGv1 = new nodegv;
    nodeGv1->gv = gv1;
    nodeGv1->next = NULL;

    // Linked list of teachers
    llgv ds_gv = nodeGv1;

    // Predefined values for searching, updating, and removing a teacher
    const char* searchMagv = "GV01";
    const char* malop = "L01";
    const char* newMagv = "GV02";

    // Search for a teacher
    tim_kiem_gv(ds_gv, searchMagv);

    // Remove a teacher from a class
    xoa_gv_khoi_lop(ds_gv, newMagv, malop);
    
    tim_kiem_gv(ds_gv, newMagv);


    return 0;
}
