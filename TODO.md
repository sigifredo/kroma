| Prioridad | Implementación                                                                             | Terminado |
| --------: | ------------------------------------------------------------------------------------------ | --------- |
|         1 | **Modo archivo real + CLI mínimo** (`kroma file.kro`)                                      | [x]       |
|         2 | **`while` + `break/continue`**                                                             | []        |
|         3 | **`for x in <range/list>` implementado como desugaring a `while`**                         | []        |
|         4 | **Asignación a índice** `a[i] = v` (`SetIndexExpr` real)                                   | []        |
|         5 | **Diccionarios (mapas)** + literal `{}` + acceso `m[key]`                                  | []        |
|         6 | **Propiedades simples** `a.b` como azúcar de `a["b"]` sobre mapas/records                  | []        |
|         7 | **Funciones**: `fun/def`, `return`, closures, y `CallExpr` completo                        | []        |
|         8 | **Builtins mínimos** (`len`, `type`, `to_string`, `assert`, etc.)                          | []        |
|         9 | **Módulos / `import` mínimo** (archivo → mapa de símbolos)                                 | []        |
|        10 | **Errores como valor** (`fail/try/is_error/panic`)                                         | []        |
|        11 | **Clases / `this` / `super`**                                                              | []        |
|        12 | **Canvas API + `loop`**                                                                    | []        |
|        13 | **Errores con localización** (línea/columna y mensaje consistente en lexer/parser/runtime) | []        |
