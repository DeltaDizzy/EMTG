/* ckmeta.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__30 = 30;
static integer c__1 = 1;
static integer c__0 = 0;
static integer c__2 = 2;

/* $Procedure      CKMETA ( CK ID to associated SCLK ) */
/* Subroutine */ int ckmeta_(integer *ckid, char *meta, integer *idcode, 
	ftnlen meta_len)
{
    /* Initialized data */

    static char base[7] = "CKMETA.";
    static integer currnt = 0;
    static logical first = TRUE_;
    static integer last = 0;
    static logical nodata = TRUE_;

    /* System generated locals */
    address a__1[2];
    integer i__1, i__2, i__3[2];

    /* Builtin functions */
    integer s_rnge(char *, integer, char *, integer), s_cmp(char *, char *, 
	    ftnlen, ftnlen);
    /* Subroutine */ int s_cat(char *, char **, integer *, integer *, ftnlen),
	     s_copy(char *, char *, ftnlen, ftnlen);

    /* Local variables */
    static integer this__, spks[30];
    extern /* Subroutine */ int zzcvpool_(char *, integer *, logical *, 
	    ftnlen), zzctruin_(integer *);
    static integer n;
    extern /* Subroutine */ int chkin_(char *, ftnlen);
    static char agent[32*30];
    extern /* Subroutine */ int errch_(char *, char *, ftnlen, ftnlen);
    static logical found[2];
    static integer sclks[30];
    extern logical failed_(void);
    extern /* Subroutine */ int clearc_(integer *, char *, ftnlen);
    extern integer bschoi_(integer *, integer *, integer *, integer *);
    static logical update;
    extern /* Subroutine */ int orderi_(integer *, integer *, integer *);
    static integer cksord[30];
    extern /* Subroutine */ int gipool_(char *, integer *, integer *, integer 
	    *, integer *, logical *, ftnlen), sigerr_(char *, ftnlen);
    static char mymeta[7];
    extern /* Subroutine */ int chkout_(char *, ftnlen), prefix_(char *, 
	    integer *, char *, ftnlen, ftnlen), ljucrs_(integer *, char *, 
	    char *, ftnlen, ftnlen), cvpool_(char *, logical *, ftnlen), 
	    dwpool_(char *, ftnlen), suffix_(char *, integer *, char *, 
	    ftnlen, ftnlen), setmsg_(char *, ftnlen);
    static char lookup[32*2*30];
    extern logical return_(void);
    static integer usrctr[60]	/* was [2][30] */;
    extern /* Subroutine */ int intstr_(integer *, char *, ftnlen), swpool_(
	    char *, integer *, char *, ftnlen, ftnlen);
    static integer cks[30];

/* $ Abstract */

/*     This routine returns (depending upon the users' request) */
/*     the ID code of either the spacecraft or spacecraft clock */
/*     associated with a C-Kernel ID code. */

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

/*     UTILITY */

/* $ Declarations */
/* $ Abstract */

/*     This include file defines the dimension of the counter */
/*     array used by various SPICE subsystems to uniquely identify */
/*     changes in their states. */

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

/* $ Parameters */

/*     CTRSIZ      is the dimension of the counter array used by */
/*                 various SPICE subsystems to uniquely identify */
/*                 changes in their states. */

/* $ Author_and_Institution */

/*     B.V. Semenov    (JPL) */

/* $ Literature_References */

/*     None. */

/* $ Version */

/* -    SPICELIB Version 1.0.0, 29-JUL-2013 (BVS) */

/* -& */

/*     End of include file. */

/* $ Brief_I/O */

/*     VARIABLE  I/O  DESCRIPTION */
/*     --------  ---  -------------------------------------------------- */
/*     CKID       I   The ID code for some C kernel object. */
/*     META       I   The kind of meta data requested 'SPK' or 'SCLK' */
/*     IDCODE     O   The ID code for the clock of the C kernel. */

/* $ Detailed_Input */

/*     CKID        is the ID code for some object whose attitude */
/*                 and possibly angular velocity are stored in */
/*                 some C-kernel. */

/*     META        is a character string that indicates which piece */
/*                 of meta data to fetch.  Acceptable values are */
/*                 'SCLK' and 'SPK'. The routine is case insensitive. */
/*                 Leading and trailing blanks are insignificant. */
/*                 However, blanks between characters are regarded */
/*                 as being significant and will result in the error */
/*                 'SPICE(UNKNOWNCKMETA)' being signaled. */

/* $ Detailed_Output */

/*     IDCODE      if META is 'SCLK' then the value returned in IDCODE */
/*                 is the "ID code" of the spacecraft clock used for */
/*                 converting ET to TICKS and TICKS to ET for the */
/*                 C-kernel used to represent the attitude of the */
/*                 object with ID code CKID. */

/*                 if META is 'SPK' then the value returned in IDCODE */
/*                 is the "ID code" of the spacecraft on which the */
/*                 platform indicated by CKID is mounted. */

/* $ Parameters */

/*      None. */

/* $ Exceptions */

/*     1) If the variable META is not recognized to be one of the */
/*        inputs 'SPK' or 'SCLK' then the error 'SPICE(UNKNOWNCKMETA)' */
/*        will be signaled. */

/*     2) If CKID is greater than -1000, the associated SCLK and SPK */
/*        ID's must be in the kernel pool.  If they are not present */
/*        a value of zero is returned for the requested item.  Zero */
/*        is never the valid ID of a spacecraft clock or ephemeris */
/*        object. */

/* $ Files */

/*     None. */

/* $ Particulars */

/*     This is a utility routine for mapping C-kernels to associated */
/*     spacecraft clocks. This is needed to facilitate the writing */
/*     of routines such as CKPG and CKGPAV. */

/* $ Examples */

/*     Suppose you would like to look up the attitude of */
/*     an object in a C-kernel but have ET and seconds as your */
/*     input time and tolerance. */

/*     This routine can be used in conjunction with SCE2C and */
/*     CKGPAV to perform this task. */

/*     CALL CKMETA ( CKID,  'SCLK'      IDCODE ) */

/*     CALL SCE2C  ( IDCODE, ET,        TICKS  ) */
/*     CALL SCE2C  ( IDCODE, ET+SECTOL, TICK2  ) */

/*     TOL = TICK2 - TICKS */

/*     CALL CKGPAV ( CKID, TICKS, TOL, REF, CMAT, AV, CLKOUT, FOUND ) */

/*     IF ( FOUND ) THEN */

/*        CALL SCT2E ( IDCODE, CLKOUT, ETOUT ) */

/*     END IF */

/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     N.J. Bachman    (JPL) */
/*     B.V. Semenov    (JPL) */
/*     W.L. Taber      (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.2.0, 06-SEP-2013 (BVS) */

/*        BUG FIX: the POOL agents now watch both variables -- */
/*        CK_<ID>_SCLK and CK_<ID>_SPK. Before they watched only */
/*        CK_<ID>_SCLK. */

/*        BUG FIX: if a previously available CK_<ID>_SCLK or CK_<ID>_SPK */
/*        variable that was used to populate a saved value disappears, */
/*        the routine now resets and returns the value based on the */
/*        default rule rather than keeping and returning the stale */
/*        POOL-based saved value. */

/*        BUG FIX: the routine now deletes watchers for the CK IDs that */
/*        were bumped from the local buffer. */

/*        Updated to keep track of agent-specific POOL counters and call */
/*        ZZCVPOOL to make use of them. */

/* -    SPICELIB Version 1.1.0, 05-MAR-2009 (NJB) */

/*        This routine now keeps track of whether its kernel pool */
/*        look-up failed. If so, a kernel pool lookup is attempted on */
/*        the next call to this routine. This change is an enhancement, */
/*        not a bug fix (unlike similar modifications in SCLK routines). */

/*        Header sections were put in correct order. */

/* -    SPICELIB Version 1.0.1, 09-MAR-1999 (NJB) */

/*        Comments referring to SCE2T have been updated to refer to */
/*        SCE2C.  Occurrences of "id" replaced by "ID." */

/* -    SPICELIB Version 1.0.0, 4-OCT-1994 (WLT) */


/* -& */
/* $ Index_Entries */

/*     Map C-kernel ID to SCLK and SPK ID */

/* -& */

/*     SPICELIB Functions */


/*     Local parameters */


/*     Local variables */


/*     Saved variables */


/*     Initial values */


/*     Standard SPICE error handling. */

    if (return_()) {
	return 0;
    }
    chkin_("CKMETA", (ftnlen)6);
    if (first) {

/*        Initialize all agent-specific POOL counters to user value. */

	for (n = 1; n <= 30; ++n) {
	    zzctruin_(&usrctr[(i__1 = (n << 1) - 2) < 60 && 0 <= i__1 ? i__1 :
		     s_rnge("usrctr", i__1, "ckmeta_", (ftnlen)275)]);
	}

/*        Clear AGENTS array. We will use a non-blank AGENT value as the */
/*        flag to delete previously set watchers. */

	clearc_(&c__30, agent, (ftnlen)32);
	first = FALSE_;
    }

/*     Get an upper-case, left-justified copy of the metadata */
/*     type ('SCLK' or 'SPK'). */

    ljucrs_(&c__1, meta, mymeta, meta_len, (ftnlen)7);

/*     See if we already have this CK ID in hand. */

    this__ = bschoi_(ckid, &currnt, cks, cksord);
    if (this__ > 0) {

/*        We've got it.  Check to see if its value has been updated. */
/*        (Note that every CK ID  has its own agent and saved POOL */
/*        counter.) */

	zzcvpool_(agent + (((i__1 = this__ - 1) < 30 && 0 <= i__1 ? i__1 : 
		s_rnge("agent", i__1, "ckmeta_", (ftnlen)305)) << 5), &usrctr[
		(i__2 = (this__ << 1) - 2) < 60 && 0 <= i__2 ? i__2 : s_rnge(
		"usrctr", i__2, "ckmeta_", (ftnlen)305)], &update, (ftnlen)32)
		;
	if (update || nodata) {
	    gipool_(lookup + (((i__1 = (this__ << 1) - 2) < 60 && 0 <= i__1 ? 
		    i__1 : s_rnge("lookup", i__1, "ckmeta_", (ftnlen)309)) << 
		    5), &c__1, &c__1, &n, &sclks[(i__2 = this__ - 1) < 30 && 
		    0 <= i__2 ? i__2 : s_rnge("sclks", i__2, "ckmeta_", (
		    ftnlen)309)], found, (ftnlen)32);
	    gipool_(lookup + (((i__1 = (this__ << 1) - 1) < 60 && 0 <= i__1 ? 
		    i__1 : s_rnge("lookup", i__1, "ckmeta_", (ftnlen)312)) << 
		    5), &c__1, &c__1, &n, &spks[(i__2 = this__ - 1) < 30 && 0 
		    <= i__2 ? i__2 : s_rnge("spks", i__2, "ckmeta_", (ftnlen)
		    312)], &found[1], (ftnlen)32);
	    if (failed_()) {
		nodata = TRUE_;
		chkout_("CKMETA", (ftnlen)6);
		return 0;
	    }

/*           Note that failure to find data is not an error in this */
/*           routine; it's just SPICE errors that are a problem. */

	    nodata = FALSE_;
	} else {

/*           The POOL variables did not change since the last check and */
/*           we have already buffered IDs for this CK ID. Set found */
/*           flags to make use of saved values. */

	    found[0] = TRUE_;
	    found[1] = TRUE_;
	}
    } else {

/*        We don't have this on our handy list. Find a place to put it. */

	if (currnt < 30) {
	    ++currnt;
	    last = currnt;
	} else {
	    ++last;
	    if (last > 30) {
		last = 1;
	    }
	}
	this__ = last;

/*        If we already have a watcher at this index, delete it. Note */
/*        we may have an update pending for this watcher, so we will */
/*        check it first to clear it. */

	if (s_cmp(agent + (((i__1 = this__ - 1) < 30 && 0 <= i__1 ? i__1 : 
		s_rnge("agent", i__1, "ckmeta_", (ftnlen)370)) << 5), " ", (
		ftnlen)32, (ftnlen)1) != 0) {
	    cvpool_(agent + (((i__1 = this__ - 1) < 30 && 0 <= i__1 ? i__1 : 
		    s_rnge("agent", i__1, "ckmeta_", (ftnlen)371)) << 5), &
		    update, (ftnlen)32);
	    dwpool_(agent + (((i__1 = this__ - 1) < 30 && 0 <= i__1 ? i__1 : 
		    s_rnge("agent", i__1, "ckmeta_", (ftnlen)372)) << 5), (
		    ftnlen)32);
	}

/*        Recompute the order vector for the CKS; construct the */
/*        kernel pool variable names and the agent name. */

	cks[(i__1 = this__ - 1) < 30 && 0 <= i__1 ? i__1 : s_rnge("cks", i__1,
		 "ckmeta_", (ftnlen)379)] = *ckid;
	orderi_(cks, &currnt, cksord);
	intstr_(ckid, lookup + (((i__1 = (this__ << 1) - 2) < 60 && 0 <= i__1 
		? i__1 : s_rnge("lookup", i__1, "ckmeta_", (ftnlen)383)) << 5)
		, (ftnlen)32);
	prefix_("CK_", &c__0, lookup + (((i__1 = (this__ << 1) - 2) < 60 && 0 
		<= i__1 ? i__1 : s_rnge("lookup", i__1, "ckmeta_", (ftnlen)
		384)) << 5), (ftnlen)3, (ftnlen)32);
/* Writing concatenation */
	i__3[0] = 7, a__1[0] = base;
	i__3[1] = 32, a__1[1] = lookup + (((i__2 = (this__ << 1) - 2) < 60 && 
		0 <= i__2 ? i__2 : s_rnge("lookup", i__2, "ckmeta_", (ftnlen)
		386)) << 5);
	s_cat(agent + (((i__1 = this__ - 1) < 30 && 0 <= i__1 ? i__1 : s_rnge(
		"agent", i__1, "ckmeta_", (ftnlen)386)) << 5), a__1, i__3, &
		c__2, (ftnlen)32);
	s_copy(lookup + (((i__1 = (this__ << 1) - 1) < 60 && 0 <= i__1 ? i__1 
		: s_rnge("lookup", i__1, "ckmeta_", (ftnlen)387)) << 5), 
		lookup + (((i__2 = (this__ << 1) - 2) < 60 && 0 <= i__2 ? 
		i__2 : s_rnge("lookup", i__2, "ckmeta_", (ftnlen)387)) << 5), 
		(ftnlen)32, (ftnlen)32);
	suffix_("_SCLK", &c__0, lookup + (((i__1 = (this__ << 1) - 2) < 60 && 
		0 <= i__1 ? i__1 : s_rnge("lookup", i__1, "ckmeta_", (ftnlen)
		389)) << 5), (ftnlen)5, (ftnlen)32);
	suffix_("_SPK", &c__0, lookup + (((i__1 = (this__ << 1) - 1) < 60 && 
		0 <= i__1 ? i__1 : s_rnge("lookup", i__1, "ckmeta_", (ftnlen)
		390)) << 5), (ftnlen)4, (ftnlen)32);

/*        Set a watch for this item and fetch the current value */
/*        from the kernel pool (if there is a value there). */

	swpool_(agent + (((i__1 = this__ - 1) < 30 && 0 <= i__1 ? i__1 : 
		s_rnge("agent", i__1, "ckmeta_", (ftnlen)396)) << 5), &c__2, 
		lookup + (((i__2 = (this__ << 1) - 2) < 60 && 0 <= i__2 ? 
		i__2 : s_rnge("lookup", i__2, "ckmeta_", (ftnlen)396)) << 5), 
		(ftnlen)32, (ftnlen)32);
	cvpool_(agent + (((i__1 = this__ - 1) < 30 && 0 <= i__1 ? i__1 : 
		s_rnge("agent", i__1, "ckmeta_", (ftnlen)398)) << 5), &update,
		 (ftnlen)32);
	gipool_(lookup + (((i__1 = (this__ << 1) - 2) < 60 && 0 <= i__1 ? 
		i__1 : s_rnge("lookup", i__1, "ckmeta_", (ftnlen)400)) << 5), 
		&c__1, &c__1, &n, &sclks[(i__2 = this__ - 1) < 30 && 0 <= 
		i__2 ? i__2 : s_rnge("sclks", i__2, "ckmeta_", (ftnlen)400)], 
		found, (ftnlen)32);
	gipool_(lookup + (((i__1 = (this__ << 1) - 1) < 60 && 0 <= i__1 ? 
		i__1 : s_rnge("lookup", i__1, "ckmeta_", (ftnlen)403)) << 5), 
		&c__1, &c__1, &n, &spks[(i__2 = this__ - 1) < 30 && 0 <= i__2 
		? i__2 : s_rnge("spks", i__2, "ckmeta_", (ftnlen)403)], &
		found[1], (ftnlen)32);
	if (failed_()) {
	    nodata = TRUE_;
	    chkout_("CKMETA", (ftnlen)6);
	    return 0;
	}

/*        Note that failure to find data is not an error in this */
/*        routine; it's just SPICE errors that are a problem. */

/*        At this point, kernel data checks are done. */

	nodata = FALSE_;
    }

/*     If we didn't find either _SCLK or _SPK variable, we manufacture */
/*     an ID code based upon the "convention" used for all CKS so far. */
/*     However, the convention assumes that the CK ID will be less than */
/*     -1000 if it's not there is no sensible ID to return.  We return */
/*     zero in that case. */

    if (! found[0]) {
	if (cks[(i__1 = this__ - 1) < 30 && 0 <= i__1 ? i__1 : s_rnge("cks", 
		i__1, "ckmeta_", (ftnlen)435)] <= -1000) {
	    sclks[(i__1 = this__ - 1) < 30 && 0 <= i__1 ? i__1 : s_rnge("scl"
		    "ks", i__1, "ckmeta_", (ftnlen)437)] = cks[(i__2 = this__ 
		    - 1) < 30 && 0 <= i__2 ? i__2 : s_rnge("cks", i__2, "ckm"
		    "eta_", (ftnlen)437)] / 1000;
	} else {
	    sclks[(i__1 = this__ - 1) < 30 && 0 <= i__1 ? i__1 : s_rnge("scl"
		    "ks", i__1, "ckmeta_", (ftnlen)441)] = 0;
	}
    }
    if (! found[1]) {
	if (cks[(i__1 = this__ - 1) < 30 && 0 <= i__1 ? i__1 : s_rnge("cks", 
		i__1, "ckmeta_", (ftnlen)449)] <= -1000) {
	    spks[(i__1 = this__ - 1) < 30 && 0 <= i__1 ? i__1 : s_rnge("spks",
		     i__1, "ckmeta_", (ftnlen)451)] = cks[(i__2 = this__ - 1) 
		    < 30 && 0 <= i__2 ? i__2 : s_rnge("cks", i__2, "ckmeta_", 
		    (ftnlen)451)] / 1000;
	} else {
	    spks[(i__1 = this__ - 1) < 30 && 0 <= i__1 ? i__1 : s_rnge("spks",
		     i__1, "ckmeta_", (ftnlen)455)] = 0;
	}
    }

/*     Set output ID. */

    if (s_cmp(mymeta, "SPK", (ftnlen)7, (ftnlen)3) == 0) {
	*idcode = spks[(i__1 = this__ - 1) < 30 && 0 <= i__1 ? i__1 : s_rnge(
		"spks", i__1, "ckmeta_", (ftnlen)466)];
    } else if (s_cmp(mymeta, "SCLK", (ftnlen)7, (ftnlen)4) == 0) {
	*idcode = sclks[(i__1 = this__ - 1) < 30 && 0 <= i__1 ? i__1 : s_rnge(
		"sclks", i__1, "ckmeta_", (ftnlen)470)];
    } else {
	*idcode = 0;
	setmsg_("The CK meta data item \"#\" is not a recognized meta data i"
		"tem for the routine CKMETA. The recognized value are \"SPK\""
		" and \"SCLK\". ", (ftnlen)128);
	errch_("#", meta, (ftnlen)1, meta_len);
	sigerr_("SPICE(UNKNOWNCKMETA)", (ftnlen)20);
	chkout_("CKMETA", (ftnlen)6);
	return 0;
    }
    chkout_("CKMETA", (ftnlen)6);
    return 0;
} /* ckmeta_ */

