# Usage 

* CREATE DATABASE <database name>;
  - <database­name> ∈ [a­zA­Z_][a­zA­Z0­9_]*

  ```
  Database db = new Database(“<database­name>”);
  db.create();
  ```

* USE DATABASE <database­name>;

  ```
  db.open(“<database­name>”);
  ```

* CREATE TABLE <table­name> (<column­name> <data­type>, ... );
  - <table­name> ∈ [a­zA­Z_][a­zA­Z0­9_]*
  - <column­name> ∈ [a­zA­Z_][a­zA­Z0­9_]*
  - <data­type> ∈ {int, string, float}

  ```
  db.create_table(
    “<table­name>”,
    {
        “<column­name>” : ”<data­type>”, 
        ... 
    }
  );
  ````

* <data­item>
  - if corresponding <data­type> is int: <data­item> ∈ [+|­]*[0­9]*
  - if corresponding <data­type> is float: <data­item> ∈ [+|­]*[0­9]*.[0­9]*
  - if corresponding <data­type> is string: <data­item> ∈ ‘.*’

* INSERT INTO <table­name> VALUES (<data­item>, ...);
  NOTE: For all columns in (3) there must be a corresponding <data­item>.
  ```
  db.insert(
    “<table­name>”,
    [“<data­item>”, ... ]
  );
  ```

* <where­clause> ∈ { WHERE <column­name> = <data­item> }

* SELECT * FROM <table­name>;
  ```
  db.select(“<table­name>”);
  ```

* SELECT * FROM <table­name> <where­clause>;
  ```
  db.select(
    “<table­name>”,
    “<column­name>”,
    “<data­item>”
  );
  ```

* SELECT <column­name>, ... FROM <table­name>;
  ```
  db.select(
    “<table­name>”,
    [“<column­name>”, ...]
  );
  ```

* SELECT <column­name>, ... FROM <table­name> <where­clause>;
  ```
  db.select(
    “<table­name>”,
    “<where­column­name>”,
    “<where­data­item>”,
    [“<column­name>”, ...]
  );
  ```

* UPDATE <table­name> SET <column­name> = <data­item> <where­clause>;
  NOTE: <data­item> should match corresponding <data­type> associated with <column­name>.
  ```
  db.update(
    “<table­name>”,
    “<column­name>”,
    “<data­item>”,
    “<where­column­name>”,
    “<where­data­item>”
  );
  ```

* DELETE FROM <table­name>;
  ```
  db.delete(“<table­name>”);
  ```

* DELETE FROM <table­name> <where­clause>;
  ```
  db.delete(
    “<table­name>”,
    “<column­name>”,
    “<data­item>”
  );
  ```

* DROP TABLE <table­name>;
  ```
  db.drop_table(“<table­name>”);
  ```

* DROP DATABASE <database­name>;
  ```
  db.drop();
  ```

* START TRANSACTION;
  ```
  db.start();
  ```

* COMMIT TRANSACTION;
  ```
  db.commit();
  ```

* ROLLBACK TRANSACTION;
  ```
  db.rollback();
  ```

* EXIT;
  ```
  db.close()
  ```