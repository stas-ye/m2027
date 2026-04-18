import pygame
import os
 
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
 

x = 20
y = 40
os.environ['SDL_VIDEO_WINDOW_POS'] = "%d,%d" % (x, y)
 
pygame.init()
 
W = 1200
H = 600
 
sc = pygame.display.set_mode((W, H))
pygame.display.set_caption("Множества Жюлиа")
sc.fill(WHITE)

c = complex(-0.2, 0.75)
P = 200                     # размер [2*P+1 x 2*P+1]
scale = P / 2               # масштабный коэффициент
n_iter = 100                # число итераций для проверки принадлежности

for y in range(-P, P):
    for x in range(-P, P):
        a = x / scale
        b = y / scale
        z = complex(a, b)
        
        n = 0
        for n in range(n_iter):
            z = z**2 + c
            if abs(z) > 2:
                break
 
        if n == n_iter - 1:
            r = g = b = 0
        else:
            r = (n % 2) * 32 + 128
            g = (n % 4) * 64
            b = (n % 2) * 16 + 128
 
        sc.set_at((x + W//2, y + H//2), (r, g, b))

FPS = 30
clock = pygame.time.Clock()
 
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            exit()
 
    clock.tick(FPS)
