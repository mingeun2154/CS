# Constraints

> ### references 🔗   
> DATABASE SYSTEM CONCEPTS ⛵️ 7th edition

## Contents		
* [외래 키 제약 조건](#)

#    

## Foregin Key Constraint

* 참조하는 릴레이션의 특정 속성값이 반드시 참조되는 릴레이션의 어떤 튜플의 해당 속성의 값으로 나와야 한다

* 속성(department의 dept_name)은 PK이어야 한다.

```SQL
department(dept_name, building, budget)
instructor(ID, name, dept_name, salary)
```

instructor 릴레이션이 instructor 릴레이션을 참조하고 있다.

