import React from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'

const styles = {
  root: {
    display: 'flex',
    justifyContent: 'flex-start',
    fontSize: 16,
    padding: 15,
  },
}

const ListItem = ({ avatar, label }) => (
  <div style={styles.root}>
    <div>{avatar}</div>
    <div>{label}</div>
  </div>
)

ListItem.propTypes = {}
ListItem.defaultProps = {}

export default Radium(ListItem)
