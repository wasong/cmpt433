import React from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'

import theme from 'theme'

const styles = {
  root: {
    backgroundColor: '#fff',
    padding: 40,
    boxShadow: theme.boxShadow,
  },
}

const FlatCard = ({ rootStyles, children }) => (
  <div style={[styles.root, rootStyles]}>
    {children}
  </div>
)

FlatCard.propTypes = {}
FlatCard.defaultProps = {}

export default Radium(FlatCard)
