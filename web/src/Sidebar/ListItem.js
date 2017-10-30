import React from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'

const styles = {
  root: {
    display: 'flex',
    justifyContent: 'flex-start',
    alignItems: 'center',
    fontSize: 14,
    padding: '0 25px',
    height: 80,
  },
  label: {
    padding: '0 0 0 25px',
  },
}

const ListItem = ({ avatar, label, labelStyle }) => (
  <div style={styles.root}>
    {avatar}
    <div style={[styles.label, labelStyle]}>{label}</div>
  </div>
)

ListItem.propTypes = {}
ListItem.defaultProps = {}

export default Radium(ListItem)
