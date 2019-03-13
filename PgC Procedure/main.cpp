extern "C" {
#include "postgres.h"
#include "fmgr.h"
#include <funcapi.h>
#include <utils/array.h>
#include <catalog/pg_type.h>
}
#include <stdlib.h>
#include <string.h>
#include "cat.h"
#include "service.h"

extern "C" {
#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif
}

extern "C"
{
    std::vector<Cat> getAllCats()
    {
        Service<Cat> service("/home/befezdow/Workspace/study/Bondin stuff/Befezdow/PgC Procedure/storage.db");
        return service.getAll();
    }
}

extern "C"
{
    PG_FUNCTION_INFO_V1(get_all_cats);
}

extern "C"
{
    Datum
    get_all_cats(PG_FUNCTION_ARGS)
    {
        FuncCallContext     *funcctx;
        int                  call_cntr;
        int                  max_calls;
        TupleDesc            tupdesc;
        AttInMetadata       *attinmeta;

        std::vector<Cat> cats = getAllCats();
        unsigned int size = cats.size();

        if (SRF_IS_FIRSTCALL())
        {
            MemoryContext   oldcontext;

            funcctx = SRF_FIRSTCALL_INIT();
            oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);
            funcctx->max_calls = size;

            if (get_call_result_type(fcinfo, NULL, &tupdesc) != TYPEFUNC_COMPOSITE)
                ereport(ERROR,
                        (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
                         errmsg("function returning record called in context "
                                "that cannot accept type record")));

            attinmeta = TupleDescGetAttInMetadata(tupdesc);
            funcctx->attinmeta = attinmeta;

            MemoryContextSwitchTo(oldcontext);
        }

        funcctx = SRF_PERCALL_SETUP();

        call_cntr = funcctx->call_cntr;
        max_calls = funcctx->max_calls;
        attinmeta = funcctx->attinmeta;

        if (call_cntr < max_calls)
        {
            char       **values;
            HeapTuple    tuple;
            Datum        result;

            values = (char **) palloc(3 * sizeof(char *));
            values[0] = (char *) palloc(64 * sizeof(char));
            values[1] = (char *) palloc(64 * sizeof(char));
            values[2] = (char *) palloc(6 * sizeof(char));

            snprintf(values[0], 64, "%s", (char*)cats[call_cntr].getName().c_str());
            snprintf(values[1], 64, "%s", (char*)cats[call_cntr].getBreed().c_str());
            snprintf(values[2], 6, "%d", cats[call_cntr].getAge());

            tuple = BuildTupleFromCStrings(attinmeta, values);
            result = HeapTupleGetDatum(tuple);

            SRF_RETURN_NEXT(funcctx, result);
        }
        else
        {
            SRF_RETURN_DONE(funcctx);
        }
    }
}
