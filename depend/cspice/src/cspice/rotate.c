/* rotate.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* $Procedure      ROTATE ( Generate a rotation matrix ) */
/* Subroutine */ int rotate_(doublereal *angle, integer *iaxis, doublereal *
	mout)
{
    /* Initialized data */

    static integer indexs[5] = { 3,1,2,3,1 };

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    double sin(doublereal), cos(doublereal);
    integer s_rnge(char *, integer, char *, integer);

    /* Local variables */
    integer temp;
    doublereal c__, s;
    integer i1, i2, i3;

/* $ Abstract */

/*      Calculate the 3x3 rotation matrix generated by a rotation */
/*      of a specified angle about a specified axis. This rotation */
/*      is thought of as rotating the coordinate system. */

/* $ Disclaimer */

/*     THIS SOFTWARE AND ANY RELATED MATERIALS WERE CREATED BY THE */
/*     CALIFORNIA INSTITUTE OF TECHNOLOGY (CALTECH) UNDER A U.S. */
/*     GOVERNMENT CONTRACT WITH THE NATIONAL AERONAUTICS AND SPACE */
/*     ADMINISTRATION (NASA). THE SOFTWARE IS TECHNOLOGY AND SOFTWARE */
/*     PUBLICLY AVAILABLE UNDER U.S. EXPORT LAWS AND IS PROVIDED "AS-IS" */
/*     TO THE RECIPIENT WITHOUT WARRANTY OF ANY KIND, INCLUDING ANY */
/*     WARRANTIES OF PERFORMANCE OR MERCHANTABILITY OR FITNESS FOR A */
/*     PARTICULAR USE OR PURPOSE (AS SET FORTH IN UNITED STATES UCC */
/*     SECTIONS 2312-2313) OR FOR ANY PURPOSE WHATSOEVER, FOR THE */
/*     SOFTWARE AND RELATED MATERIALS, HOWEVER USED. */

/*     IN NO EVENT SHALL CALTECH, ITS JET PROPULSION LABORATORY, OR NASA */
/*     BE LIABLE FOR ANY DAMAGES AND/OR COSTS, INCLUDING, BUT NOT */
/*     LIMITED TO, INCIDENTAL OR CONSEQUENTIAL DAMAGES OF ANY KIND, */
/*     INCLUDING ECONOMIC DAMAGE OR INJURY TO PROPERTY AND LOST PROFITS, */
/*     REGARDLESS OF WHETHER CALTECH, JPL, OR NASA BE ADVISED, HAVE */
/*     REASON TO KNOW, OR, IN FACT, SHALL KNOW OF THE POSSIBILITY. */

/*     RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF */
/*     THE SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY */
/*     CALTECH AND NASA FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE */
/*     ACTIONS OF RECIPIENT IN THE USE OF THE SOFTWARE. */

/* $ Required_Reading */

/*     None. */

/* $ Keywords */

/*      MATRIX,  ROTATION */

/* $ Declarations */
/* $ Brief_I/O */

/*      VARIABLE  I/O              DESCRIPTION */
/*      --------  ---  -------------------------------------------------- */
/*       ANGLE     I     Angle of rotation (radians). */
/*       IAXIS     I     Axis of rotation (X=1, Y=2, Z=3). */
/*       MOUT      O     Resulting rotation matrix [ANGLE] */
/*                                                       IAXIS */
/* $ Detailed_Input */

/*      ANGLE   The angle given in radians, through which the rotation */
/*              is performed. */

/*      IAXIS   The index of the axis of rotation.  The X, Y, and Z */
/*              axes have indices 1, 2 and 3 respectively. */

/* $ Detailed_Output */

/*      MOUT    Rotation matrix which describes the rotation of the */
/*               COORDINATE system through ANGLE radians about the */
/*               axis whose index is IAXIS. */

/* $ Parameters */

/*      None. */

/* $ Particulars */

/*      A rotation about the first, i.e. x-axis, is described by */

/*      |  1        0          0      | */
/*      |  0   cos(theta) sin(theta)  | */
/*      |  0  -sin(theta) cos(theta)  | */

/*      A rotation about the second, i.e. y-axis, is described by */

/*      |  cos(theta)  0  -sin(theta)  | */
/*      |      0       1        0      | */
/*      |  sin(theta)  0   cos(theta)  | */

/*      A rotation about the third, i.e. z-axis, is described by */

/*      |  cos(theta) sin(theta)   0   | */
/*      | -sin(theta) cos(theta)   0   | */
/*      |       0          0       1   | */

/*      ROTATE decides which form is appropriate according to the value */
/*      of IAXIS. */

/* $ Examples */

/*      If ROTATE is called from a FORTRAN program as follows: */

/*            CALL ROTATE (PI/4, 3, MOUT) */

/*      then MOUT will be given by */

/*                   | SQRT(2)/2   SQRT(2)/2   0  | */
/*            MOUT = |-SQRT(2)/2   SQRT(2)/2   0  | */
/*                   |     0           0       1  | */

/* $ Restrictions */

/*      None. */

/* $ Exceptions */

/*     Error free. */

/*     1) If the axis index is not in the range 1 to 3 it will be */
/*        treated the same as that integer 1, 2, or 3 that is congruent */
/*        to it mod 3. */

/* $ Files */

/*      None. */

/* $ Author_and_Institution */

/*      W.M. Owen       (JPL) */
/*      W.L. Taber      (JPL) */

/* $ Literature_References */

/*      None. */

/* $ Version */

/* -    SPICELIB Version 1.0.1, 10-MAR-1992 (WLT) */

/*        Comment section for permuted index source lines was added */
/*        following the header. */

/* -    SPICELIB Version 1.0.0, 31-JAN-1990 (WMO) */

/* -& */
/* $ Index_Entries */

/*     generate a rotation matrix */

/* -& */
/* $ Revisions */

/* -    Beta Version 1.1.0, 3-JAN-1989 (WLT) */

/*     Upgrade the routine to work with negative axis indexes.  Also take */
/*     care of the funky way the indices (other than the input) were */
/*     obtained via the MOD function.  It works but isn't as clear */
/*     (or fast) as just reading the axes from data. */

/* -& */



/*  Get the sine and cosine of ANGLE */

    s = sin(*angle);
    c__ = cos(*angle);

/*  Get indices for axes. The first index is for the axis of rotation. */
/*  The next two axes follow in right hand order (XYZ).  First get the */
/*  non-negative value of IAXIS mod 3 . */

    temp = (*iaxis % 3 + 3) % 3;
    i1 = indexs[(i__1 = temp) < 5 && 0 <= i__1 ? i__1 : s_rnge("indexs", i__1,
	     "rotate_", (ftnlen)189)];
    i2 = indexs[(i__1 = temp + 1) < 5 && 0 <= i__1 ? i__1 : s_rnge("indexs", 
	    i__1, "rotate_", (ftnlen)190)];
    i3 = indexs[(i__1 = temp + 2) < 5 && 0 <= i__1 ? i__1 : s_rnge("indexs", 
	    i__1, "rotate_", (ftnlen)191)];

/*  Construct the rotation matrix */

    mout[(i__1 = i1 + i1 * 3 - 4) < 9 && 0 <= i__1 ? i__1 : s_rnge("mout", 
	    i__1, "rotate_", (ftnlen)196)] = 1.;
    mout[(i__1 = i2 + i1 * 3 - 4) < 9 && 0 <= i__1 ? i__1 : s_rnge("mout", 
	    i__1, "rotate_", (ftnlen)197)] = 0.;
    mout[(i__1 = i3 + i1 * 3 - 4) < 9 && 0 <= i__1 ? i__1 : s_rnge("mout", 
	    i__1, "rotate_", (ftnlen)198)] = 0.;
    mout[(i__1 = i1 + i2 * 3 - 4) < 9 && 0 <= i__1 ? i__1 : s_rnge("mout", 
	    i__1, "rotate_", (ftnlen)199)] = 0.;
    mout[(i__1 = i2 + i2 * 3 - 4) < 9 && 0 <= i__1 ? i__1 : s_rnge("mout", 
	    i__1, "rotate_", (ftnlen)200)] = c__;
    mout[(i__1 = i3 + i2 * 3 - 4) < 9 && 0 <= i__1 ? i__1 : s_rnge("mout", 
	    i__1, "rotate_", (ftnlen)201)] = -s;
    mout[(i__1 = i1 + i3 * 3 - 4) < 9 && 0 <= i__1 ? i__1 : s_rnge("mout", 
	    i__1, "rotate_", (ftnlen)202)] = 0.;
    mout[(i__1 = i2 + i3 * 3 - 4) < 9 && 0 <= i__1 ? i__1 : s_rnge("mout", 
	    i__1, "rotate_", (ftnlen)203)] = s;
    mout[(i__1 = i3 + i3 * 3 - 4) < 9 && 0 <= i__1 ? i__1 : s_rnge("mout", 
	    i__1, "rotate_", (ftnlen)204)] = c__;

    return 0;
} /* rotate_ */

