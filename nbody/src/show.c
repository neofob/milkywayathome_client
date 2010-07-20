/* Copyright 2010 Matthew Arsenault, Travis Desell, Dave Przybylo,
Nathan Cole, Boleslaw Szymanski, Heidi Newberg, Carlos Varela, Malik
Magdon-Ismail and Rensselaer Polytechnic Institute.

This file is part of Milkway@Home.

Milkyway@Home is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Milkyway@Home is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Milkyway@Home.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <string.h>
#include "nbody_util.h"
#include "nbody_types.h"
#include "show.h"

/* A bunch of boilerplate for debug printing */

const char* showBool(const bool x)
{
    switch (x)
    {
        case FALSE:
            return "false";
        case TRUE:
            return "true";
        default:
            return "invalid boolean (but true)";
    }
}

const char* showCriterionT(const criterion_t x)
{
    static const char* table[] =
        {
            [EXACT]        = "exact",
            [NEWCRITERION] = "new criterion",
            [BH86]         = "bh86",
            [SW93]         = "sw93"
        };

    if (x > SW93)
        return "invalid criterion_t";
    else
        return table[x];

}

const char* showSphericalT(const spherical_t x)
{
    static const char* table[] =
        {
            [SphericalPotential]        = "SphericalPotential",
        };

    if (x > SphericalPotential)
        return "invalid spherical_t";
    else
        return table[x];
}

const char* showDiskT(const disk_t x)
{
    static const char* table[] =
        {
            [MiyamotoNagaiDisk] = "MiyamotoNagaiDisk",
            [ExponentialDisk]   = "ExponentialDisk"
        };

    if (x > ExponentialDisk)
        return "invalid disk_t";
    else
        return table[x];
}

const char* showHaloT(const halo_t x)
{
    static const char* table[] =
        {
            [LogarithmicHalo] = "LogarithmicHalo",
            [NFWHalo]         = "NFWHalo",
            [TriaxialHalo]    = "TriaxialHalo"
        };

    if (x > TriaxialHalo)
        return "invalid halo_t";
    else
        return table[x];
}

const char* showDwarfModelT(const dwarf_model_t x)
{
    static const char* table[] =
        {
            [DwarfModelPlummer] = "DwarfModelPlummer",
            [DwarfModelKing]    = "DwarfModelKing",
            [DwarfModelDehnen]  = "DwarfModelDehnen"
        };

    if (x > DwarfModelDehnen)
        return "invalid dwarf_model_t";
    else
        return table[x];
}

char* showSpherical(const Spherical* s)
{
    char* buf;

    if (0 > asprintf(&buf,
                     "{\n"
                     "      type  = %s\n"
                     "      mass  = %g\n"
                     "      scale = %g\n"
                     "    };\n",
                     showSphericalT(s->type),
                     s->mass,
                     s->scale))
    {
        fail("asprintf() failed\n");
    }

    return buf;
}

char* showHalo(const Halo* h)
{
    char* buf;

    if (0 > asprintf(&buf,
                     "{ \n"
                     "      type         = %s\n"
                     "      vhalo        = %g\n"
                     "      scale_length = %g\n"
                     "      flattenX     = %g\n"
                     "      flattenY     = %g\n"
                     "      flattenZ     = %g\n"
                     "      triaxAngle   = %g\n"
                     "    };\n",
                     showHaloT(h->type),
                     h->vhalo,
                     h->scale_length,
                     h->flattenX,
                     h->flattenY,
                     h->flattenZ,
                     h->triaxAngle))
    {
        fail("asprintf() failed\n");
    }

    return buf;
}

char* showDisk(const Disk* d)
{
    char* buf;

    if (0 > asprintf(&buf,
                     "{ \n"
                     "      type         = %s\n"
                     "      mass         = %g\n"
                     "      scale_length = %g\n"
                     "      scale_height = %g\n"
                     "    };\n",
                     showDiskT(d->type),
                     d->mass,
                     d->scale_length,
                     d->scale_height))
    {
        fail("asprintf() failed\n");
    }

    return buf;
}

/* For debugging. Need to make this go away for release since it uses
 * GNU extensions */
char* showPotential(const Potential* p)
{
    int rc;
    char* buf;
    char* sphBuf;
    char* diskBuf;
    char* haloBuf;

    sphBuf  = showSpherical(&p->sphere[0]);
    diskBuf = showDisk(&p->disk);
    haloBuf = showHalo(&p->halo);

    rc = asprintf(&buf,
                  "{\n"
                  "    sphere = %s\n"
                  "    disk = %s\n"
                  "    halo = %s\n"
                  "    rings  = { unused pointer %p }\n"
                  "  };\n",
                  sphBuf,
                  diskBuf,
                  haloBuf,
                  p->rings);

    if (rc < 0)
        fail("asprintf() failed\n");

    free(sphBuf);
    free(diskBuf);
    free(haloBuf);

    return buf;
}

char* showDwarfModel(const DwarfModel* d)
{
    char* buf;

    if (0 > asprintf(&buf,
                     "{ \n"
                     "      type           = %s\n"
                     "      nbody          = %d\n"
                     "      mass           = %g\n"
                     "      scale_radius   = %g\n"
                     "      timestep       = %g\n"
                     "      orbit_timestep = %g\n"
                     "      time_dwarf     = %g\n"
                     "      time_orbit     = %g\n"
                     "      eps            = %g\n"
                     "    };\n",
                     showDwarfModelT(d->type),
                     d->nbody,
                     d->mass,
                     d->scale_radius,
                     d->timestep,
                     d->orbit_timestep,
                     d->time_orbit,
                     d->time_dwarf,
                     d->eps))
    {
        fail("asprintf() failed\n");
    }

    return buf;
}

char* showInitialConditions(const InitialConditions* ic)
{
    char* buf;
    if (0 > asprintf(&buf,
                     "initial-conditions = { \n"
                     "  useGalC    = %s\n"
                     "  useRadians = %s\n"
                     "  position   = { %g, %g, %g }\n"
                     "  velocity   = { %g, %g, %g }\n"
                     "};\n",
                     showBool(ic->useGalC),
                     showBool(ic->useRadians),
                     ic->position[0],
                     ic->position[1],
                     ic->position[2],
                     ic->velocity[0],
                     ic->velocity[1],
                     ic->velocity[2]))
    {
        fail("asprintf() failed\n");
    }

    return buf;
}

char* showContext(const NBodyCtx* ctx)
{
    char* buf;
    char* potBuf;
    char* modelBuf;

    potBuf   = showPotential(&ctx->pot);
    modelBuf = showDwarfModel(&ctx->model);

    if (0 > asprintf(&buf,
                     "ctx = { \n"
                     "  pot             = %s\n"
                     "  model           = %s\n"
                     "  headline        = %s\n"
                     "  outfilename     = %s\n"
                     "  histogram       = %s\n"
                     "  histout         = %s\n"
                     "  outfile         = %p\n"
                     "  sunGCDist       = %g\n"
                     "  criterion       = %s\n"
                     "  usequad         = %s\n"
                     "  allowIncest     = %s\n"
                     "  outputCartesian = %s\n"
                     "  seed            = %ld\n"
                     "  tree_rsize      = %g\n"
                     "  theta           = %g\n"
                     "  freqout         = %g\n"
                     "};\n",
                     potBuf,
                     modelBuf,
                     ctx->headline,
                     ctx->outfilename,
                     ctx->histogram,
                     ctx->histout,
                     ctx->outfile,
                     ctx->sunGCDist,
                     showCriterionT(ctx->criterion),
                     showBool(ctx->usequad),
                     showBool(ctx->allowIncest),
                     showBool(ctx->outputCartesian),
                     ctx->seed,
                     ctx->tree_rsize,
                     ctx->theta,
                     ctx->freqout))
    {
        fail("asprintf() failed\n");
    }

    free(potBuf);
    free(modelBuf);

    return buf;
}

void printContext(const NBodyCtx* ctx)
{
    char* buf = showContext(ctx);
    puts(buf);
    free(buf);
}

void printInitialConditions(const InitialConditions* ic)
{
    char* buf = showInitialConditions(ic);
    puts(buf);
    free(buf);
}

char* showVector(const vector v)
{
    char* buf;

    if (asprintf(&buf, "{ %g, %g, %g }", v[0], v[1], v[2]) < 0)
        fail("asprintf() failed\n");

    return buf;

}

void printVector(const vector v)
{
    char* buf = showVector(v);
    puts(buf);
    free(buf);
}

char* showFitParams(const FitParams* fp)
{
    char* buf;
    if (0 > asprintf(&buf,
                     "fit-params  = { \n"
                     "  useFitParams     = %s\n"
                     "  modelMass        = %g\n"
                     "  modelRadius      = %g\n"
                     "  reverseOrbitTime = %g\n"
                     "  simulationTime   = %g\n"
                     "};\n",
                     showBool(fp->useFitParams),
                     fp->modelMass,
                     fp->modelRadius,
                     fp->reverseOrbitTime,
                     fp->simulationTime))

    {
        fail("asprintf() failed\n");
    }

    return buf;
}

void printFitParams(const FitParams* fp)
{
    char* buf = showFitParams(fp);
    puts(buf);
    free(buf);
}

