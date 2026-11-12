# 🛡️ Audit de Sécurité Mémoire & Modernisation C++ (Legacy Refactoring)

Ce dépôt présente un cas pratique d'audit critique et de refactorisation d'un module réseau C++ *Legacy* (`PacketBuffer`). L'objectif est d'éliminer les vulnérabilités mémoire critiques tout en garantissant la portabilité multi-compilateurs et la maintenabilité du code.

## 🔍 1. Diagnostic des failles critiques (Code Legacy)

L'audit statique et dynamique du module d'origine a mis en évidence **6 vulnérabilités majeures** :
1. **Dépassement de tampon (*Heap Buffer Overflow*)** : Allocation de `strlen(input)` octets sans réserver d'espace pour le caractère nul de fin de chaîne (`\0`).
2. **Double libération mémoire (*Double Free*)** : Absence de constructeur de copie entraînant une copie superficielle (*Shallow Copy*) des pointeurs bruts et un crash à la destruction.
3. **Comportement indéfini (*Undefined Behavior*)** : Utilisation de `delete` au lieu de `delete[]` pour libérer un tableau alloué dynamiquement.
4. **Fuite mémoire (*Memory Leak*)** : Réaffectation du pointeur interne dans la méthode `append()` sans libération préalable de l'ancien bloc mémoire.
5. **Déréférencement de pointeur nul** : Absence de vérification face aux entrées `nullptr`, provoquant un arrêt brutal du processus.
6. **Violation de la Règle des 3 / Règle des 5** : Absence d'opérateur d'affectation par copie (`operator=`).

## ✅ 2. Architecture et Solutions Appliquées

Pour sécuriser durablement ce composant, l'architecture a été revue selon les standards du **C++ moderne** :
* **Application de la Règle de 0 & RAII** : Remplacement des allocations manuelles (`char*`, `new`/`delete`) par `std::string` pour garantir une gestion automatique, sûre et sans fuite de la mémoire.
* **Programmation défensive** : Validation systématique des pointeurs entrants (`nullptr`) dans le constructeur et les méthodes de mutation.
* **Portabilité multi-compilateurs** : Compilation validée sous **Embarcadero C++Builder** (Windows) et **Visual Studio MSVC x64** (avec AddressSanitizer) ainsi que compatibilité standard GCC/Clang.

## 🚀 3. Validation et Tests

Le programme intègre une suite de tests fonctionnels validant :
* L'indépendance mémoire lors de la copie d'objets (`PacketBuffer p2 = p1`).
* La résistance aux pointeurs nuls (`PacketBuffer(nullptr)` et `append(nullptr)`).
* Une sortie propre sans fuite mémoire (`Exit Code: 0`).

---
*Auteur : **Noureddine Fenniche** — Tech Lead C++ & Architecte Logiciel*
