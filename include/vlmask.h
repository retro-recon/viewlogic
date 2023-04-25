/*
 * $Id: vlmask.h,v 1.4.7.1 1995/10/17 20:40:12 cway Stab $
 *
 * Created -- Peter Colby -- October 1991
 *
 * Copyright 1991 Viewlogic Systems, Inc.
 */

#ifndef vlMask_H
#define vlMask_H

/*\Section vlMask -- Macros to help deal with masks
 * 
 * DESCRIPTION
 *      Masks are held in an unsigned long, typedef'd as vlMaskT in vldefs.h.
 *      These macros all take a bit number, which is an integer ranging from
 *      0 to 31 on platforms that have 32 bit longs.
 */

#define vlMaskBITS_PER_MASK 32

/*\Docpage vlMaskALL_OFF -- a constant mask with no bits set.
 * 
 * EXAMPLE
 *      if (err_mask != vlMaskALL_OFF)
 *         vlErrThrow (...);
 */
#define vlMaskALL_OFF 0L

/*\Docpage vlMaskTURN_ON -- Turn on the specified bit in the mask
 * 
 * SYNOPSIS
 *      vlMaskTURN_ON (vlMaskT mask, int bit);
 */
#define vlMaskTURN_ON(mask, bit) ((mask) |= (1 << (bit)))

/*\Docpage vlMaskTURN_OFF -- Turn off the specified bit in the mask
 * 
 * SYNOPSIS
 *      vlMaskTURN_OFF (vlMaskT mask, int bit);
 */
#define vlMaskTURN_OFF(mask, bit) ((mask) &= ~(1 << (bit)))

/*\Docpage vlMaskSET -- Set the specified bit in the mask to on or off
 * 
 * SYNOPSIS
 *      vlMaskSET (vlMaskT mask, int bit, vlBoolT on_off);
 */
#define vlMaskSET(mask, bit, on_off) \
    ((on_off) ? vlMaskTURN_ON (mask, bit) : vlMaskTURN_OFF (mask, bit))

/*\Docpage vlMaskGET -- Check if specified bit is on
 * 
 * SYNOPSIS
 *      vlBoolT vlMaskGET (vlMaskT mask, int bit);
 *
 * DESCRIPTION
 *      Returns non-zero (boolean true) if the bit is on or zero if
 *      it is off.  Use vlMaskVALUE if you want 1 or 0 instead.
 *
 * SEE ALSO
 *      vlMaskVALUE
 */
#define vlMaskGET(mask, bit) (((mask) & (1 << (bit))) != 0)

/*\Docpage vlMaskVALUE -- Check if specified bit is on
 * 
 * SYNOPSIS
 *      int vlMaskVALUE (vlMaskT mask, int bit);
 * 
 * DESCRIPTION
 *      Same as vlMaskGET but guarrantees a '1' if the bit is set.
 *      Use vlMaskGET if you just want a boolean value.
 *
 * SEE ALSO
 *      vlMaskVALUE
 */
#define vlMaskVALUE(mask, bit) ((vlMaskGET((mask), (bit))) ? 1 : 0)

/*\Docpage vlMaskTOGGLE -- Change specified bit in the mask
 * 
 * SYNOPSIS
 *      vlMaskTOGGLE (vlMaskT mask, int bit);
 * 
 * DESCRIPTION
 *      If specified bit is on, turn it off, otherwise turn it on.
 */
#define vlMaskTOGGLE(mask, bit) \
    (vlMaskSET (mask, bit, !vlMaskGET (mask, bit)))

/*\Docpage vlMaskTURN_ON_ALL -- Turn on all bits in mask
 * 
 * SYNOPSIS 
 *      vlMaskTURN_ON_ALL (mask)
 */
#define vlMaskTURN_ON_ALL(mask) (mask) = ~(vlMaskALL_OFF)

/*\Docpage vlMaskTURN_OFF_ALL -- Turn off all bits in mask
 * 
 * SYNOPSIS
 *      vlMaskTURN_OFF_ALL (mask)
 */
#define vlMaskTURN_OFF_ALL(mask) (mask) = vlMaskALL_OFF

/*\Docpage vlMaskTOGGLE_ALL -- Toggle all bits in mask
 * 
 * SYNOPSIS
 *      vlMaskTOGGLE_ALL(mask)
 */
#define vlMaskTOGGLE_ALL(mask) (mask) ^= ~(vlMaskALL_OFF)

#endif
