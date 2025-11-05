Ceci est une documntation pour cub3D

## Formule mathematique 

Pour un angle θ (theta) et une distance d :

 déplacement_horizontal (Δx) = cos(θ) × d
déplacement_vertical   (Δy) = sin(θ) × d

Exemples :

### 1
angle = 0°
max_distance = 100

cos(0°) = 1
sin(0°) = 0

end.x = start.x + (1 × 100) = start.x + 100
end.y = start.y + (0 × 100) = start.y + 0

Résultat : Le rayon va tout droit vers la droite ➡️

start ●━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━● end (10, 10)                                        (110, 10)

### 2

angle = 90°
max_distance = 100

cos(90°) = 0
sin(90°) = 1

end.x = start.x + (0 × 100) = start.x + 0
end.y = start.y + (1 × 100) = start.y + 100


///// On a tendance a mettre start.x + 1 pour start pour ce cas on avance de 100

Résultat : Le rayon va tout droit vers le haut ⬆️

                  end ●
                     (10, 110)
                      |
                      |
                      |
                      |
                      |
                start ●
                     (10, 10)

### 3

angle = 45°
max_distance = 100

cos(45°) ≈ 0.707
sin(45°) ≈ 0.707

end.x = start.x + (0.707 × 100) = start.x + 70.7
end.y = start.y + (0.707 × 100) = start.y + 70.7

Résultat : Le rayon va en diagonale ↗️

To do a division by right shift we must do 

15 / 2 est equivaut a 15 >> 1

15 / 4 est equivaut a 15 >> 2 car 4 = 2^2

15 / 2^n equivaut a  15 >> n

