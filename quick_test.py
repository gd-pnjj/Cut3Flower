import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation, PillowWriter

t = np.linspace(-0.1, 0.5, 100)


def f(x, y):
    return np.sign(x) * np.sign(y) * y**4 + np.sign(x) * x**4 - (1 / x ** (1 / 5)) * (1 / y ** (1 / 5))


def g(x, y, t):
    return t * f(x, y)


# Create meshgrid avoiding 0,0, spanning -10 to 10
eps = 0.01
x = np.concatenate([np.linspace(-10, -eps, 75), np.linspace(eps, 10, 75)])
y = np.concatenate([np.linspace(-10, -eps, 75), np.linspace(eps, 10, 75)])
X, Y = np.meshgrid(x, y)

# Set up figure
fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')


def update(frame):
    ax.clear()
    t_cur = t[frame]
    Z = g(X, Y, t_cur)
    surf = ax.plot_surface(X, Y, Z, cmap='viridis', edgecolor='none')
    ax.set_title(f'g(x,y,t) | t = {t_cur:.3f}')
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('g')
    ax.set_xlim(-10, 10)
    ax.set_ylim(-10, 10)
    ax.set_zlim(-6, 8)
    return surf,


ani = FuncAnimation(fig, update, frames=len(t), blit=False, interval=50)
ani.save('g_evolution.gif', writer=PillowWriter(fps=20))
plt.close(fig)

print('Saved g_evolution.gif')