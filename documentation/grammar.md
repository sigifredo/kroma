# 📘 Extensión de la Gramática – Kroma

Este documento extiende la gramática del lenguaje **Kroma** para incluir tokens adicionales como llaves, paréntesis, operadores, llamadas a funciones, control de flujo, y declaraciones.

---

## 🧱 Gramática extendida (EBNF)

```ebnf
program        → declaration* EOF ;

declaration    → varDecl
               | funDecl
               | classDecl
               | statement ;

varDecl        → "let" IDENTIFIER ( "=" expression )? ";" ;

funDecl        → "fun" IDENTIFIER "(" parameters? ")" block ;

classDecl      → "class" IDENTIFIER ( "<" IDENTIFIER )? "{" function* "}" ;

parameters     → IDENTIFIER ( "," IDENTIFIER )* ;

statement      → exprStmt
               | printStmt
               | returnStmt
               | ifStmt
               | whileStmt
               | forStmt
               | block ;

exprStmt       → expression ";" ;

printStmt      → "print" expression ";" ;

returnStmt     → "return" expression? ";" ;

ifStmt         → "if" "(" expression ")" statement ( "else" statement )? ;

whileStmt      → "while" "(" expression ")" statement ;

forStmt        → "for" "(" varDecl | exprStmt | ";" expression? ";" expression? ")" statement ;

block          → "{" declaration* "}" ;

expression     → assignment ;

assignment     → IDENTIFIER "=" assignment
               | logic_or ;

logic_or       → logic_and ( "or" logic_and )* ;

logic_and      → equality ( "and" equality )* ;

equality       → comparison ( ( "!=" | "==" ) comparison )* ;

comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;

term           → factor ( ( "-" | "+" ) factor )* ;

factor         → unary ( ( "/" | "*" ) unary )* ;

unary          → ( "!" | "-" ) unary
               | call ;

call           → primary ( "(" arguments? ")" | "." IDENTIFIER )* ;

arguments      → expression ( "," expression )* ;

primary        → NUMBER
               | STRING
               | "true"
               | "false"
               | "null"
               | "this"
               | IDENTIFIER
               | "(" expression ")"
               | "super" "." IDENTIFIER ;
```

---

## 📌 Nuevos tokens cubiertos

| Token           | Regla donde se usa            | Descripción                                 |
| --------------- | ----------------------------- | ------------------------------------------- |
| `(` `)`         | `call`, `ifStmt`, `whileStmt` | Paréntesis para agrupar o invocar funciones |
| `{` `}`         | `block`                       | Agrupación de múltiples sentencias          |
| `,`             | `arguments`, `parameters`     | Separador de parámetros y argumentos        |
| `.`             | `call`                        | Acceso a métodos (`objeto.metodo()`)        |
| `-` `+`         | `term`, `unary`               | Operadores aritméticos                      |
| `/` `*`         | `factor`                      | Operadores multiplicativos                  |
| `!`, `!=`       | `unary`, `equality`           | Negación y desigualdad                      |
| `=`, `==`       | `assignment`, `equality`      | Asignación y comparación                    |
| `>`, `>=`       | `comparison`                  | Comparadores mayores                        |
| `<`, `<=`       | `comparison`                  | Comparadores menores                        |
| `and`, `or`     | `logic_and`, `logic_or`       | Operadores lógicos                          |
| `let`           | `varDecl`                     | Declaración de variable                     |
| `fun`           | `funDecl`                     | Declaración de función                      |
| `class`         | `classDecl`                   | Declaración de clase                        |
| `if`, `else`    | `ifStmt`                      | Condicionales                               |
| `for`, `while`  | `forStmt`, `whileStmt`        | Bucles                                      |
| `print`         | `printStmt`                   | Imprimir valores                            |
| `return`        | `returnStmt`                  | Devolver valores de funciones               |
| `this`, `super` | `primary`                     | Contexto de clases                          |

---

## 🧪 Ejemplo de programa válido

```kroma
class Pincel {
  fun trazar(x, y) {
    print(x + y);
  }
}

let p = Pincel();
p.trazar(100, 200);
```

---

## 🔍 Observaciones

- Todas las sentencias terminan con `;`, excepto los bloques `{}`.
- Las llamadas anidadas y encadenadas están permitidas: `obj.metodo().otroMetodo()`.
- El operador `.` permite acceso a propiedades o métodos de objetos y clases.
- El `if`, `while`, y `for` siempre usan paréntesis para sus condiciones.
