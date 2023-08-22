#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define SHM_KEY 1234
#define SHM_SIZE 1024

int main() {
    int shmid;
    char *shared_memory;
    int pipefd[2];

    // 创建管道
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // 创建共享内存段
    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        return 1;
    }

    // 将共享内存段附加到进程的地址空间
    shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)-1) {
        perror("shmat");
        return 1;
    }

    // 创建子进程
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) { // 子进程
        close(pipefd[1]); // 关闭写端
        char buf;
        read(pipefd[0], &buf, 1); // 从管道读取，这会阻塞直到主进程写入数据
        close(pipefd[0]);

        printf("Child: Reading from shared memory...\n");
        printf("Child: Received message: %s\n", shared_memory);
    } else { // 主进程
        strcpy(shared_memory, "Hello from parent process!");
        printf("Parent: Message written to shared memory.\n");

        close(pipefd[0]); // 关闭读端
        write(pipefd[1], "x", 1); // 写入数据到管道，这会使子进程从阻塞中恢复
        close(pipefd[1]);

        wait(NULL); // 等待子进程结束
    }

    // 从进程的地址空间中分离共享内存段
    shmdt(shared_memory);

    // 删除共享内存段
    if (pid != 0) {
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
