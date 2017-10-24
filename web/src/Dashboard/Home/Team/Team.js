import React from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'

import Divider from 'material-ui/Divider'
import FlatCard from 'components/FlatCard'

const styles = {
  title: {
    fontSize: 18,
    margin: '0 0 5px',
    color: '#b1b1b1',
  },
  teamCard: {
    height: 500,
    margin: '0 40px 0 0',
    flex: 2,
  },
}

const Team = props => (
  <FlatCard rootStyles={styles.teamCard}>
    <div style={styles.title}>TEAM</div>
    <Divider />
  </FlatCard>
)

Team.propTypes = {}
Team.defaultProps = {}

export default Radium(Team)
