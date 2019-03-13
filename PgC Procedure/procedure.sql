CREATE TYPE _cats AS (name varchar(64), breed varchar(64), age smallint);

CREATE OR REPLACE FUNCTION allCats()
    RETURNS SETOF _cats
    AS '/home/befezdow/Workspace/study/Bondin stuff/Befezdow/PgC Procedure/catslib.so', 'get_all_cats'
    LANGUAGE C IMMUTABLE STRICT;
