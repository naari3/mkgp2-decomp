# objdiff absolute-symbol prettification

`Rand_RangeIntMax` demonstrates an objdiff false negative: the target literal
`0x80010003` may be rendered as the nearby absolute symbol
`@etb_8000FFF8+0xB`, while identical new bytes are rendered numerically. This
can lower the semantic score (observed: 99.565216%) despite byte-identical
instructions. Compare encoded instructions and the final linked SHA-1 when
this presentation-only difference appears.
