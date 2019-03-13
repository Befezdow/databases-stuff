CREATE OR REPLACE FUNCTION add_teacher() RETURNS TRIGGER AS $$
    BEGIN
        IF (TG_OP = 'UPDATE' AND NEW.login IS NOT NULL) THEN
            EXECUTE 'REVOKE teachers FROM ' || OLD.login;
            EXECUTE 'GRANT teachers TO ' || NEW.login;
            RETURN NULL;
        ELSIF (TG_OP = 'INSERT' AND NEW.login IS NOT NULL) THEN
            EXECUTE 'GRANT teachers TO ' || NEW.login;
            RETURN NULL;
        ELSIF (TG_OP = 'DELETE') THEN
            EXECUTE 'REVOKE teachers FROM ' || OLD.login;
            RETURN NULL;
        END IF;
        RETURN NULL;
    END;
$$ LANGUAGE PLPGSQL;

CREATE OR REPLACE FUNCTION add_pupil() RETURNS TRIGGER AS $$
    BEGIN
        IF (TG_OP = 'UPDATE' AND NEW.login IS NOT NULL) THEN
            EXECUTE 'REVOKE pupils FROM ' || OLD.login;
            EXECUTE 'GRANT pupils TO ' || NEW.login;
            RETURN NULL;
        ELSIF (TG_OP = 'INSERT' AND NEW.login IS NOT NULL) THEN
            EXECUTE 'GRANT pupils TO ' || NEW.login;
            RETURN NULL;
        ELSIF (TG_OP = 'DELETE') THEN
            EXECUTE 'REVOKE pupils FROM ' || OLD.login;
            RETURN NULL;
        END IF;
        RETURN NULL;
    END;
$$ LANGUAGE PLPGSQL;

CREATE OR REPLACE FUNCTION add_admin() RETURNS TRIGGER AS $$
    BEGIN
        IF (TG_OP = 'UPDATE' AND NEW.login IS NOT NULL) THEN
            EXECUTE 'REVOKE admins FROM ' || OLD.login;
            EXECUTE 'ALTER ROLE ' || OLD.login || ' WITH NOCREATEROLE';
            EXECUTE 'GRANT admins TO ' || NEW.login;
            EXECUTE 'ALTER ROLE ' || NEW.login || ' WITH CREATEROLE';
            RETURN NULL;
        ELSIF (TG_OP = 'INSERT' AND NEW.login IS NOT NULL) THEN
            EXECUTE 'GRANT admins TO ' || NEW.login;
            EXECUTE 'ALTER ROLE ' || NEW.login || ' WITH CREATEROLE';
            RETURN NULL;
        ELSIF (TG_OP = 'DELETE') THEN
            EXECUTE 'REVOKE admins FROM ' || OLD.login;
            EXECUTE 'ALTER ROLE ' || OLD.login || ' WITH NOCREATEROLE';
            RETURN NULL;
        END IF;
        RETURN NULL;
    END;
$$ LANGUAGE PLPGSQL;

DROP TRIGGER IF EXISTS add_teacher_trigger ON teacher CASCADE;
DROP TRIGGER IF EXISTS add_pupil_trigger ON pupil CASCADE;
DROP TRIGGER IF EXISTS add_admin_trigger ON admin CASCADE;

CREATE TRIGGER add_teacher_trigger AFTER INSERT OR UPDATE ON teacher
    FOR EACH ROW EXECUTE PROCEDURE add_teacher();
CREATE TRIGGER add_pupil_trigger AFTER INSERT OR UPDATE ON pupil
    FOR EACH ROW EXECUTE PROCEDURE add_pupil();
CREATE TRIGGER add_admin_trigger AFTER INSERT OR UPDATE ON admin
    FOR EACH ROW EXECUTE PROCEDURE add_admin();